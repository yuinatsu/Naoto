#include <DxLib.h>
#include "GmkEvent.h"
#include "SoundPross.h"
#include "../Object/Enemy.h"
#include "../Component/Navi/Navi.h"

GmkEvent::GmkEvent()
{
	flag_ = false;
	scFlag_ = true;
	sColor_ = 255.0f;
	Time_ = 0.0f;
	SoundProcess::Init();
	SoundProcess::Load(LoadSoundMem("./Resource/Sound/Caveat.mp3"), SoundProcess::ESOUNDNAME_SE::waring);
	nowType_ = EventType::Non;
	gmkFunc_.reserve(static_cast<size_t>(EventType::Non));

	gmkFunc_.emplace(
		EventType::Alert,
		std::make_pair(
			std::bind(&GmkEvent::AlertUpdate, this, std::placeholders::_1),
			std::bind(&GmkEvent::AlertDraw, this)));
	gmkFunc_.emplace(
		EventType::Enemy,
		std::make_pair(
		[](float delta) {},
		[](){SetDrawBright(255, 255, 255); }));
	gmkFunc_.emplace(EventType::Non, gmkFunc_[EventType::Enemy]);
}

GmkEvent::~GmkEvent()
{
	SoundProcess::Release();
}

void GmkEvent::DisPlayer(bool flag, float delta)
{
	if (flag_ == false)
	{
		flag_ = flag;
	}
	if (flag_ && Time_ <= 4)
	{
		if (Time_ == 0.0f)
		{
			SoundProcess::DoSound(SoundProcess::ESOUNDNAME_SE::waring);
		}
		Time_ += delta;
		if (sColor_ <= 255.0f && !scFlag_)
		{
			SetDrawBright(255, static_cast<int>(sColor_), static_cast<int>(sColor_));
			sColor_ += delta * 150.0f;
			if (sColor_ > 255.0f)
			{
				scFlag_ = true;
			}
		}
		if (sColor_ >= 100.0f && scFlag_)
		{
			SetDrawBright(255, static_cast<int>(sColor_), static_cast<int>(sColor_));
			sColor_ -= delta * 150.0f;
			if (sColor_ < 100.0f)
			{
				scFlag_ = false;
			}
		}
	}
	else
	{
		SetDrawBright(255, 255, 255);
		SoundProcess::SEEnd(SoundProcess::ESOUNDNAME_SE::waring);
		scFlag_ = true;
		sColor_ = 255.0f;
		Time_ = 0.0f;
		flag_ = false;
	}
}

void GmkEvent::StartEvent(std::list<std::unique_ptr<Obj>>& enemyList, const Math::Vector2& pos, EventType type)
{

	// 現在の発生中のギミックとのチェック
	if (nowType_ == type || (nowType_ == EventType::Alert && type != EventType::Alert))
	{
		// 同じギミックもしくは監視カメラの時それ以外のギミックイベントの時処理をやめる
		return;
	}
	nowType_ = type;
	gmkStepTime_ = 0.0f;

	auto& enemy = dynamic_cast<Enemy&>(**enemyList.begin());
	enemy.SetState(EnemyState::Gimic);
	dynamic_cast<Navi&>((*enemyList.begin())->GetComponent(ComponentID::Navi, "Navi")).Search((*enemyList.begin())->GetPos(), pos);
	if (EventType::Alert == nowType_)
	{
		SoundProcess::DoSound(SoundProcess::ESOUNDNAME_SE::waring);
	}
}

// ギミックイベントの持続時間
constexpr float gmkMaxTime{ 4.0f };

void GmkEvent::Update(float delta)
{
	gmkStepTime_ += delta;
	gmkFunc_[nowType_].first(delta);
}

void GmkEvent::Draw(void)
{
	gmkFunc_[nowType_].second();
}

void GmkEvent::AlertUpdate(float delta)
{
	if (sColor_ <= 255.0f && !scFlag_)
	{

		sColor_ += delta * 150.0f;
		if (sColor_ > 255.0f)
		{
			scFlag_ = true;
		}
	}
	if (sColor_ >= 100.0f && scFlag_)
	{
		sColor_ -= delta * 150.0f;
		if (sColor_ < 100.0f)
		{
			scFlag_ = false;
		}
	}
	if (gmkStepTime_ > gmkMaxTime)
	{
		SoundProcess::SEEnd(SoundProcess::ESOUNDNAME_SE::waring);
		nowType_ = EventType::Non;
	}
}

void GmkEvent::AlertDraw(void)
{
	SetDrawBright(255, static_cast<int>(sColor_), static_cast<int>(sColor_));
}

