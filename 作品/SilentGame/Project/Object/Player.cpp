#include "Player.h"
#include "../Input/Keyboard.h"
#include "../Input/Pad.h"
#include "../common/rapidxml.hpp"
#include "../common/rapidxml_utils.hpp"
#include "../common/AnimMng.h"
#include "../Component/Animation.h"
#include "../common/ImageMng.h"
#include "../common/Debug.h"

// アニメーション参照用
constexpr char AnimCompName[]{ "PlayerAnim" };

Player::Player(CntType cntType, std::shared_ptr<TmxObj> tmx, Math::Vector2 pos)
{
	// 初期化
	tmx_ = tmx;
	pos_ = pos;
	Init(cntType);
}

Player::~Player()
{
	delete animNode_;
}

bool Player::Init(CntType cntType)
{
	// プレイヤーのイメージとアニメーション読み込み
	if (!LoadAnim())
	{
		return false;
	}		

	// コントローラ情報
	if (cntType == CntType::Key)
	{
		// キーボード
		controller_ = std::make_unique<Keyboard>();
	}
	if (cntType == CntType::Pad)
	{
		// ゲームパッド
		controller_ = std::make_unique<Pad>();
	}

	// プレイヤーアクション読み込み
	rapidxml::file<> attach = "Resource/Xml/PlayerAction.tsx";
	stateVec_ = attach.vecData();
	stateDoc_.parse<0>(stateVec_.data());
	stateNode_ = stateDoc_.first_node("objectList");
	animNode_ = new animNode();

	// Effect
	lpImageMng.GetID("Resource/Image/Effect/slash.png", "effect", Math::Vector2{ 64,64 }, { 9,1 });

	return true;
}

void Player::Update(double delta)
{
	delta_ = delta;
	// キー処理
	if (!(*controller_)(delta))
	{
		// コントローラ情報が無かったらはじく
		return;
	}
	// プレイヤーの行動処理
	for (auto node = stateNode_->first_node(); node != nullptr; node = node->next_sibling())
	{
		animNode()(this, node);
	}
	// アニメーション更新
	UpdateComponent(delta);
	// コントローラー更新
	controller_->Update(delta);
}

void Player::Draw(const Math::Vector2& offset)
{
	// Vector2 check(colPos_);
	// プレイヤー表示
	dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, AnimCompName)).Draw(pos_ + offset, size_, isIdle_);
	DrawEffect(offset);
}

void Player::DrawEffect(const Math::Vector2& offset)
{
	if (atkFlag_)
	{
		int n = 8;
		for (int i = 0; i < (n * 1); i++)
		{
			DrawGraph(pos_.x + offset.x - 30, pos_.y + offset.y - 30, lpImageMng.GetID("effect")[(i / 1) + 1], true);                       // キャラチップ
		}
		atkFlag_ = false;
	}
}

bool Player::LoadAnim(void)
{
	bool rtnflag = true;
	// 返り値のFlagチェック
	auto check = [&rtnflag](bool flag)
	{
		// 一つでも偽があれば返り値はfalse
		rtnflag &= flag;
	};
	// アニメーションの種類
	std::array<std::string, 4> list = { "Down","Left","Right","Up" };

	// アニメーションクラス追加
	AddComponent(std::make_unique<Animation>("Player", AnimCompName, *this));
	// アニメーションクラス取得
	auto& anim = dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, AnimCompName));
	// 外部からxmlを取得しSetXmlに格納
	check(lpAnimMng.SetXml(anim.GetKey(), "Resource/Xml/PlayerImage.tsx"));
	for (auto& data : list)
	{
		check(lpAnimMng.SetItem(anim.GetKey(), data));
	}
	// アニメーション初期化
	anim.state("Down");
	// プレイヤーサイズ取得
	size_ = lpAnimMng.GetImageSize(anim.GetKey());
	return rtnflag;
}
