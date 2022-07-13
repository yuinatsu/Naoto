#include "Enemy.h"
#include <DxLib.h>
#include "../common/Random.h"
#include "../Component/Collider/CircleCollider.h"
#include "../common/ImageMng.h"
#include "../common/AnimMng.h"

#include "../common/Debug.h"

#include "../Component/Collider/FanCollider.h"
#include "../Component/Navi/Navi.h"
#include "../Component/Navi/PatrolNavi.h"
#include "../Component/Animation.h"

#include "../common/Structure.h"

// 通常時のスピード
constexpr float speed{ 2.0f };

// 追跡時のスピード
constexpr float runSpeed{13.0f};

constexpr float fov{ Math::Deg2Rad(45.0f) };

constexpr char animCompName[]{ "Anim" };

#ifdef _DEBUG
// 以下デバッグ用
constexpr char pat[]{ "Patrol" };
constexpr char non[]{ "Non" };

constexpr const char* DebugStateStr(EnemyState state)
{
	switch (state)
	{
	case EnemyState::Trace:
		return "Trace";
	case EnemyState::Sound:
		return "Sound";
	case EnemyState::Gimic:
		return "Gimic";
	case EnemyState::Patrol:
		return "Patrol";
	case EnemyState::MovePatrol:
		return "MovePatrol";
	case EnemyState::Non:
		return "Non";
	case EnemyState::Item:
		return "Item";
	case EnemyState::Lost:
		return "Lost";
	case EnemyState::Look:
		return "Look";
	default:
		return "Non";
	}
}
#else
#define DebugStateStr() ()
#endif
Enemy::Enemy(std::vector<Math::Vector2I>& route,std::shared_ptr<TmxObj>& tmxObj, const Math::Vector2& pos)
{
	pos_ =  pos;
	stateTime_ = 0.0f;
	tmx_ = tmxObj;
	
	isIdle_ = false;
	moveVec_ = { -1.0f, 0.0f };
	state_ = EnemyState::Sound;

	auto angle = moveVec_.GetAngle();
	Math::Vector2 v1{std::cos(angle - fov/2.0f), std::sin(angle - fov/2.0f)};
	Math::Vector2 v2{ std::cos(angle + fov / 2.0f), std::sin(angle + fov / 2.0f) };
	v1 *= 120.0f;
	v2 *= 120.0f;

	// 視界の当たり判定を追加
	AddComponent(std::make_unique<FanCollider>(tmx_,v1, v2, [this](Collider& other) {
		// ステートチェック(アイテムをくらった時もしくは追跡中は関係ない)
		if (state_ == EnemyState::Item || other.GetName() != "BodyCol") return;
		if (!(state_ == EnemyState::Trace || state_ == EnemyState::Look))
		{
			SetState(EnemyState::Look);
			dynamic_cast<PatrolNavi&>(GetComponent(ComponentID::PatrolNavi, "Patrol")).Stop();
		}
		
		moveVec_ = (other.GetOwner().GetPos() - pos_).Normalized();

		},
		"Fan",*this
		)
	);
	speed_ = 2.5f;
	spMag_ = 1.0f;
	// 経路探索用クラスをセット
	AddComponent(std::make_unique<Navi>(tmx_,"Navi", *this));
	
	
	// 巡回用クラスをセット
	AddComponent(std::make_unique<PatrolNavi>(route, tmx_, "Patrol", *this));

	AddComponent(std::make_unique<Animation>("Enemy", animCompName, *this));
	auto& anim = dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, animCompName));
	lpAnimMng.SetXml("Enemy","Resource/Xml/enemyAnim.xml");
	const std::array<std::string, 4> stateList{ "Down","Left","Right","Up" };
	
	for (auto& state : stateList)
	{
		lpAnimMng.SetItem("Enemy", state);
	}
	anim.state("Down");


	Init();
	state_ = EnemyState::Non;
}

Enemy::~Enemy()
{
}


EnemyState Enemy::GetEnemyState(void) const
{
	return state_;
}

void Enemy::SetRotationAngle(float angle)
{
	targetAngle_ = angle;
	Math::Vector2 targetVec = { std::cos(targetAngle_), std::sin(targetAngle_) };
	angleSing_ = Math::Cross(moveVec_, targetVec) > 0.0f ? 1.0f : -1.0f;

}

void Enemy::SetRotationAngle(void)
{
	targetAngle_ = (-moveVec_).GetAngle();
	Math::Vector2 targetVec = { std::cos(targetAngle_), std::sin(targetAngle_) };
	angleSing_ = Math::Cross(moveVec_, targetVec) > 0.0f ? 1.0f : -1.0f;
}

void Enemy::Rotation(double delta)
{
	dynamic_cast<FanCollider&>(GetComponent(ComponentID::Collider, "Fan")).AddAngle(rotSpeed_ * angleSing_);
	auto angle = moveVec_.GetAngle() + rotSpeed_ * angleSing_;
	moveVec_ = { std::cos(angle), std::sin(angle) };
}

void Enemy::SetState(EnemyState state)
{
	state_ = state;
	stateTime_ = 0.0f;
	DebugLog(DebugStateStr(state_));
}

void Enemy::CorrectMoveVecToAnim(void)
{
	
	auto ckFunc = [this](const Math::Vector2& rV, const Math::Vector2& lV)
	{
		if (Math::Cross(moveVec_, rV) < 0.0f &&  Math::Cross(moveVec_, lV) > 0.0f )
		{
			return true;
		}
		return false;
	};

	if (ckFunc(Math::downVector2<float> +Math::rightVector2<float>, Math::downVector2<float> +Math::leftVector2<float>))
	{
		dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, "EnemyAnim")).state("Down");
		return;
	}

	if (ckFunc(Math::upVector2<float> +Math::leftVector2<float>, Math::upVector2<float> +Math::rightVector2<float>))
	{
		dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, "EnemyAnim")).state("Up");
		return;
	}

	if (ckFunc(Math::downVector2<float> +Math::leftVector2<float>, Math::upVector2<float> +Math::leftVector2<float>))
	{
		dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, "EnemyAnim")).state("Left");
		return;
	}

	if (ckFunc(Math::upVector2<float> +Math::rightVector2<float>, Math::downVector2<float> +Math::rightVector2<float>))
	{
		dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, "EnemyAnim")).state("Right");
		return;
	}
	
}

const float Enemy::GetStateTime(void) const
{
	return stateTime_;
}

bool Enemy::Init(void)
{
	auto f = [this](Collider& other) { 
		//if (other.GetName() != "body") { return; }
		if (!(state_ == EnemyState::Trace || state_ == EnemyState::Item) && !other.GetOwner().IsIdle() && other.GetOwner().GetObjID() == ObjID::Player)
		{
			SetState(EnemyState::Sound);
			dynamic_cast<PatrolNavi&>(GetComponent(ComponentID::PatrolNavi, "Patrol")).Stop();
			SetRotationAngle((other.GetOwner().GetPos() - pos_).GetAngle());
		}
	};
	AddComponent(std::make_unique<CircleCollider>(
		10.0f, 
		[this](Collider& other) { 
			if (state_ == EnemyState::Trace && other.GetOwner().GetObjID() == ObjID::Player && other.GetName() == "BodyCol")
			{
				if (other.GetName() == "BodyCol")
				{
					// プレイヤーを死亡させる処理
					other.GetOwner().Destroy();
				}
			}
			if (other.GetOwner().GetObjID() == ObjID::Decoy)
			{
				// デコイの時の処理
				other.GetOwner().Destroy();
				SetState(EnemyState::Lost);
			}
			if (other.GetOwner().GetObjID() == ObjID::Alcohol)
			{
				// アルコールアイテムの時の処理
				other.GetOwner().Destroy();
				SetState(EnemyState::Item);
			}
		},
		"BodyCol", 
		*this)
	);
	return AddComponent(std::make_unique<CircleCollider>(30.0f, f, "SoundCol", *this));
}

void Enemy::Update(double delta)
{
	spMag_ = 1.0f;
	auto angle = moveVec_.GetAngle();
	Math::Vector2 v1{ std::cos(angle - fov / 2.0f), std::sin(angle - fov / 2.0f) };
	Math::Vector2 v2{ std::cos(angle + fov / 2.0f), std::sin(angle + fov / 2.0f) };
	dynamic_cast<FanCollider&>(GetComponent(ComponentID::Collider, "Fan")).SetAngleFromVec(v1, v2);
	UpdateComponent(delta);
	stateTime_ += static_cast<float>(delta);
}

void Enemy::Draw(const Math::Vector2& offset)
{
	auto& anim = dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, animCompName));
	anim.Draw(pos_ + offset, Math::zeroVector2<int>, isIdle_);
	//for (auto& d : GetComponent(ComponentID::Collider))
	//{
	//	d.second->DbgDraw(offset);
	//}

	/*auto tmpVec = moveVec_ * 30.0f;
	DrawLine(
		static_cast<int>(pos_.x + offset.x), static_cast<int>(pos_.y + offset.y),
		static_cast<int>(pos_.x + tmpVec.x + offset.x), static_cast<int>(pos_.y + tmpVec.y + offset.y),
		0xffffff);*/
}
