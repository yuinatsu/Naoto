#include <DxLib.h>
#include "../../common/ImageMng.h"
#include "../../common/Structure.h"
#include "../ObjManager.h"
#include "../UI/ItemUi.h"
#include "Box.h"

#include "../../common/nameof.hpp"

constexpr char openImg[]{ "./Resource/Image/openBox.png" };
constexpr char closeImg[]{ "./Resource/Image/box.png" };


Box::Box(UiBase& itemUi,const Math::Vector2& pos, ObjManager& objMng, ItemName itemName) :
	objMng_{objMng}, itemName_{itemName}, itemUi_{itemUi}
{
	pos_ = pos;
	squar_ = std::make_unique<Squar>(pos + Math::Vector2{ -16.0f, -16.0f }, pos + Math::Vector2{ 16.0f, 16.0f });
	Init();
}

Box::~Box()
{
}

void Box::Init(void)
{
	flag_ = false;
	sColor_ = 255;
	scFlag_ = true;
	lpImageMng.GetID("./Resource/Image/box.png");
	lpImageMng.GetID("./Resource/Image/openBox.png");
}

void Box::Update(double delta)
{
	squar_->Update(objMng_.GetPlayer().GetPos());
	if (!flag_ && !BelFlag_)
	{
		BelFlag_ = squar_->flag_;
		if (BelFlag_)
		{
			std::string str(NAMEOF_ENUM(itemName_).data());
			if (itemUi_.SetItemID(std::make_pair(static_cast<int>(itemName_), str)))
			{
				BelFlag_ = true;
				flag_ = true;
			}
			else
			{
				BelFlag_ = false;
			}
		}
	}

}


void Box::Draw(const Vector2& drawoffset)
{
	DrawRotaGraph(static_cast<int>(pos_.x + drawoffset.x), static_cast<int>(pos_.y + drawoffset.y), 1.0, 0.0, lpImageMng.GetID((flag_ == true ? openImg : closeImg))[0], true);
}

bool Box::GetFlag(void)
{
	return BelFlag_;
}
