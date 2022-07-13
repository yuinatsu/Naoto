#include <DxLib.h>
#include <algorithm>
#include "ItemUi.h"
#include "../../common/ImageMng.h"
#include "../../common/nameof.hpp"		// 外部データ
#include "../../common/Debug.h"


ItemUi::ItemUi(const Math::Vector2& pos, const Math::Vector2& scrSize) : UiBase(pos, scrSize)
{
	size_ = { 32,32 };
	useItem_ = ItemName::Max;
	mask_ = LoadMask("Resource/Image/UI/UIMask.png");
	lpImageMng.GetID("Resource/Image/UI/itemIcon.png", "Icon", size_, { 4,1 });

	rapidxml::file<> attach = "Resource/Xml/PlayerAction.tsx";
	stateVec_ = attach.vecData();
	stateDoc_.parse<0>(stateVec_.data());
	stateNode_ = stateDoc_.first_node("objectList");
	animNodeUI_ = new animNodeUI();
}

ItemUi::~ItemUi()
{
	delete animNodeUI_;
}

void ItemUi::Update(const double& delta)
{
	for (auto node = stateNode_->first_node(); node != nullptr; node = node->next_sibling())
	{
		//animNodeUI()(this, node);
	}
	controller_->Update(delta);
	if (controller_->Pressed(InputID::ItemLeft))
	{
		// 左回転
		if (order_.size())
		{
			std::rotate(order_.begin(), order_.begin() + (order_.size() - 1), order_.end());
		}
	}
	if (controller_->Pressed(InputID::ItemRight))
	{
		// 右回転
		if (order_.size())
		{
			std::rotate(order_.begin(), order_.begin() + 1, order_.end());
		}
	}
	auto tmp = controller_->LongPress(InputID::Attack, 3.0, delta);
	if (tmp == "Attack" && order_.size())
	{
		// 使用したアイテムの情報格納
		useItem_ = static_cast<ItemName>(order_.at(0).first);
		if (useItem_ != ItemName::Knife)
		{
			// 先頭要素削除
			order_.erase(order_.begin());
		}
	}
	//else if (tmp == "LongAttack" && order_.size())
	//{
	//	// 使用したアイテムの情報格納
	//	useItem_ = static_cast<ItemName>(order_.at(0).first);
	//	if (useItem_ != ItemName::Knife)
	//	{
	//		// 先頭要素削除
	//		order_.erase(order_.begin());
	//	}
	//}
	// ソート
	for (int i = 0; i < order_.size(); i++)
	{
		bool isLead = false;
		if (!i)
		{
			isLead = true;
		}
		order_.at(i).second = isLead;
	}
}

void ItemUi::ItemUpdate(const double& delta)
{
	if (order_.size() >= haveItemMax)
	{
		return;
	}
	for (auto& id : id_)
	{
		for (int n = 0; n < id_.size(); n++)
		{
			for (int i = 0; i < static_cast<int>(ItemName::Max); i++)
			{
				if (NAMEOF_ENUM(static_cast<ItemName>(i)) != id.second)
				{
					continue;
				}
				bool isLead = false;
				if (!i)
				{
					isLead = true;
				}
				order_.push_back(std::make_pair(i,isLead));
				break;
			}
			break;
		}
	}
	id_.clear();
}

void ItemUi::UIDraw(const double& delta)
{
	auto size = Vector2{ 269,128 };
	auto pos = Vector2{ 20,550 };
	SetUseMaskScreenFlag(true);
	DrawMask(pos.x, pos.y, mask_, DX_MASKTRANS_NONE);
	DrawBox(pos.x, pos.y, pos.x + size.x, pos.y + size.y, 0xffff00, true);
	SetUseMaskScreenFlag(false);
	ItemDraw(pos);
}

void ItemUi::ItemDraw(const Math::Vector2& pos)
{
	auto itemPos = Vector2{ pos.x + 25,pos.y + 20 };
	for (int i = 0; i < order_.size(); i++)
	{
		if (order_.at(i).second)
		{
			DrawExtendGraph(itemPos.x, itemPos.y, itemPos.x + size_.x * 2, itemPos.y + size_.y * 2, lpImageMng.GetID("Icon")[order_.at(i).first], true);
		}
		else
		{
			DrawGraph(itemPos.x + size_.x + size_.x * i, itemPos.y + size_.y, lpImageMng.GetID("Icon")[order_.at(i).first], true);
		}
	}
}

bool ItemUi::SetItemID(std::pair<int, std::string> id)
{
	if (order_.size() < haveItemMax)
	{
		id_.push_back(id);
		return true;
	}
	return false;
}

ItemName ItemUi::GetUseItem()
{
	auto name = useItem_;
	useItem_ = ItemName::Max;
	return name;
}
