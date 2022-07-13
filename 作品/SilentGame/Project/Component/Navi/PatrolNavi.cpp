#include "../../Object/Obj.h"
#include "../../Resource/Tmx/TmxObj.h"
#include "PatrolNavi.h"

PatrolNavi::PatrolNavi(Vector2lVec& route,std::shared_ptr<TmxObj>& tmxObj,const std::string& name, Obj& owner) :
	Component{name, owner}, patrolRoute_{route}, tmxObj_{tmxObj}
{
	// テスト用巡回路
	/*patrolRoute_.emplace_back(Math::Vector2I{ 29, 14 });
	patrolRoute_.emplace_back(Math::Vector2I{ 2,14 });
	patrolRoute_.emplace_back(Math::Vector2I{ 2,37 });
	patrolRoute_.emplace_back(Math::Vector2I{ 29,37 });*/
	patrolPos_ = patrolRoute_.begin();
	stopFlag_ = true;
}

const Math::Vector2 PatrolNavi::GetMovePos(void) const
{
	return static_cast<Math::Vector2>(*patrolPos_ * tmxObj_->GetTileSize() + tmxObj_->GetTileSize() / 2);
}

const Math::Vector2I& PatrolNavi::GetPos(void) const
{
	return *patrolPos_;
}

bool PatrolNavi::IsStop(void) const
{
	return stopFlag_;
}

void PatrolNavi::Stop(void)
{
	stopFlag_ = true;
}

void PatrolNavi::Start(void)
{
	stopFlag_ = false;
}

void PatrolNavi::Update(float delta)
{
	// ストップフラグをチェックする
	if (stopFlag_)
	{
		// ストップの時これ以上処理しない
		return;
	}

	auto& tileSize = tmxObj_->GetTileSize();
	const auto&& pos = static_cast<Math::Vector2I>(owner_.GetPos()) / tileSize;
	if (pos == *patrolPos_)
	{
		++patrolPos_;
		if (patrolPos_ == patrolRoute_.end())
		{
			patrolPos_ = patrolRoute_.begin();
		}
	}
}

ComponentID PatrolNavi::GetID() const
{
	return ComponentID::PatrolNavi;
}
