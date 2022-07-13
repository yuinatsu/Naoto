#include <DxLib.h>
#include "Animation.h"
#include "../common/AnimMng.h"
#include "../common/ImageMng.h"
#include "../common/Debug.h"

Animation::Animation(const std::string& key, const std::string& name, Obj& owner):
	Component{name,owner}, key_(key)
{
	state_ = "Down";
	Init();
}

Animation::Animation(const std::string& key, const std::string& name, std::pair<int, std::string> id, Obj& owner):
	Component{ name,owner }, key_(key)
{
	state_ = id.second;
	Init();
}

Animation::~Animation()
{
}

bool Animation::Init(void)
{
	animCount_ = 0;
	animFrame_ = 0;
	return true;
}

void Animation::Update(float delta)
{
	if (!lpAnimMng.CheckAnim(key_, state_))
	{
		return ;
	}
	if (animFrame_ < 0 || animFrame_ >= lpAnimMng.GetAnimSize(key_, state_))
	{
		return ;
	}
	if (animCount_++ >= lpAnimMng.GetAnimFrame(key_, state_, animFrame_))
	{
		if (lpAnimMng.GetAnimID(key_, state_, animFrame_) >= 0)
		{
			animFrame_ += 1;
		}
	}
	if (animFrame_ >= lpAnimMng.GetAnimSize(key_, state_))
	{
		animFrame_ = 0;
		animCount_ = 0;
	}
	return ;
}

bool Animation::Draw(Math::Vector2 pos, Math::Vector2I size, bool flag)
{
	if (flag)
	{
		DrawRotaGraph(pos.x, pos.y, 1.0f, 0.0f, lpAnimMng.GetAnimID(key_, state_, 1), true);
	}
	else
	{
		DrawRotaGraph(pos.x, pos.y, 1.0f, 0.0f, lpAnimMng.GetAnimID(key_, state_, animFrame_), true);
	}
	return true;
}

bool Animation::Draw(Math::Vector2 pos, Math::Vector2I size, std::string state)
{
	DrawRotaGraph(pos.x, pos.y, 1.0f, 0.0f, lpAnimMng.GetAnimID(key_, state, animFrame_), true);
	return true;
}

bool Animation::state(const std::string state)
{
	if (lpAnimMng.CheckAnim(key_, state))
	{
		if (state != state_)
		{
			animFrame_ = 0;
			animCount_ = 0;
		}
		state_ = state;
		return true;
	}
	return false;
}

std::string Animation::GetKey(void)
{
	return key_;
}

std::string Animation::GetState(void)
{
	return state_;
}

ComponentID Animation::GetID() const
{
	return ComponentID::Animator;
}
