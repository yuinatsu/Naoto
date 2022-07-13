#include <DxLib.h>
#include "TrapAlarm.h"
#include "../ObjManager.h"
#include "../../common//ImageMng.h"
#include "../../common/Structure.h"
#include "../../common/SoundPross.h"

constexpr char closeImg[]{ "./Resource/Image/boxAlarm.png" };
constexpr char openImg[]{ "./Resource/Image/boxAlarm1.png" };

TrapAlarm::TrapAlarm(const Math::Vector2& pos, ObjManager& objMng):
	objMng_(objMng)
{
	pos_ = pos;
	squar_ = std::make_unique<Squar>(pos + Math::Vector2{ -16,-16 }, pos + Math::Vector2{ 16,16 });
	Init();
}

TrapAlarm::~TrapAlarm()
{
	SoundProcess::Release();
}

void TrapAlarm::Init(void)
{
	sTime_ = 0.0f;
	lpImageMng.GetID("./Resource/Image/boxAlarm.png");
	lpImageMng.GetID("./Resource/Image/boxAlarm1.png");
}

void TrapAlarm::Update(double delta)
{
	squar_->Update(objMng_.GetPlayer().GetPos());
	if (!flag_)
	{
		flag_ = squar_->flag_;
	}
	if (flag_ && sTime_ <= 4)
	{
		if (sTime_ == 0.0f)
		{
			pflag_ = true;
			sPos_ = objMng_.GetPlayer().GetPos();
		}
		else
		{
			sPos_ = (0.0f, 0.0f);
			pflag_ = false;
		}
		sTime_ += static_cast<float>(delta);
	}
	else
	{
		sTime_ = 0.0f;
		flag_ = false;
	}
}

void TrapAlarm::Draw(const Math::Vector2& offset)
{
	DrawRotaGraph(static_cast<int>(pos_.x + offset.x), static_cast<int>(pos_.y + offset.y), 1.0, 0.0, lpImageMng.GetID((flag_ == true ? openImg : closeImg))[0], true);
}

Vector2 TrapAlarm::GetSpos(void)
{
	return sPos_;
}

bool TrapAlarm::GetpFlag(void)
{
	return pflag_;
}

