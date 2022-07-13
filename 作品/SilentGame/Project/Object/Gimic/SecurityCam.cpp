#include <DxLib.h>
#include <math.h>
#include "SecurityCam.h"
#include "../../common/SoundPross.h"


Alert::Alert(Vector2 pos, Vector2 vec,std::shared_ptr<TmxObj>& tmxObj, std::unique_ptr<Obj>& player) :
	 tmxObj_(tmxObj), player_(player)
{
	rotFlag_ = true;
	Time_ = 0;
	sFlag_ = false;
	rotTime_ = 1.0f;
	sPos_ = { 0.0f,0.0f };
	fan_ = std::make_unique<Fan>(pos, vec* Vector2{112,112}, DX_PI_F / 5.0f, tmxObj_->GetColList(), tmxObj_->GetCol2List());
	Init();
}


Alert::~Alert()
{
	SoundProcess::Release();
}

void Alert::Init(void)
{

}

void Alert::Update(double delta)
{
	// éãê¸Ç…ÉvÉåÉCÉÑÅ[Ç™Ç¢Ç»ÇØÇÍÇŒÇ§ÇÎÇ§ÇÎÇ∑ÇÈ
	if (!sFlag_)
	{
		UpdateNoDis(player_.get()->GetPos(), delta);

	}
	else
	{
		UpdateDis(player_.get()->GetPos(), delta);
	}
}


// å©Ç¬ÇØÇƒÇ¢Ç»Ç¢Ç∆Ç´ÇÃèàóù
void Alert::UpdateNoDis(const Vector2& pos, float delta)
{
	float Deg = Math::GetNormalizedAngle(fan_->GetAngle(), Math::Deg2Rad(0.0f), Math::Deg2Rad(360.0f));
	float Rad = Math::Rad2Deg(Deg);
	auto flag = fan_->UpdateHitRect(pos);
	rotTime_ -= delta;
	//a
	if (flag && rotFlag_ && rotTime_ <= -1.0f)
	{
		rotTime_ = 1.0f;
		rotFlag_ = false;
	}
	else if (flag && !rotFlag_ && rotTime_ <= -1.0f)
	{
		rotTime_ = 1.0f;
		rotFlag_ = true;
	}
	if (rotFlag_ && rotTime_ <= 0.0f)
	{
		fan_->AddAngle(0.003f);
	}
	if (!rotFlag_ && rotTime_ <= 0.0f)
	{
		fan_->AddAngle(-0.003f);
	}

	if (fan_->UpdateHitPos(pos))
	{
		sFlag_ = true;
		SetPos(pos);
	}
}

// å©Ç¬ÇØÇΩéûÇÃèàóù
void Alert::UpdateDis(const Vector2& pos, float delta)
{
	if (sFlag_ && Time_ <= 4)
	{
		
		if (Time_ == 0.0f)
		{
			pflag_ = true;
			sPos_ = pos;
		}
		else
		{
			sPos_ = (0.0f, 0.0f);
			pflag_ = false;
		}
		Time_ += delta;
	}
	else
	{
		Time_ = 0.0f;
		sFlag_ = false;
	}
}

void Alert::Draw(const Math::Vector2& offset)
{
	if (!sFlag_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		fan_->Draw(offset);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

Vector2 Alert::GetSpos(void)
{
	return sPos_;
}

bool Alert::GetpFlag(void)
{
	return pflag_;
}

void Alert::SetPos(const Vector2& pos)
{
	sPos_ = pos;
	return;
}

