#include <dxlib.h>
#include "Star.h"
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"


Star::Star(Vector2Flt&& pos, Vector2Flt&& size) : Shape(pos, size)
{
}


Star::~Star()
{
}


void Star::Update(float delta, ShapeVec& shapeVec)
{
	if (flag1)
	{
		pos_.x_ += 300 * delta;
		if (pos_.x_ + size_.x_ >= 1024)
		{
			flag1 = false;
			color_ = 0xff0000;
		}
	}
	if (!flag1)
	{
		pos_.x_ -= 300 * delta;
		if (pos_.x_ - size_.x_ <= 0)
		{
			flag1 = true;
			color_ = 0x0000ff;
		}
	}
}


void Star::Draw(void)
{
	DrawTriangle((int)pos_.x_, (int)pos_.y_, (int)(pos_.x_ - size_.x_), (int)(pos_.y_ + size_.y_), (int)(pos_.x_ + size_.x_), (int)(pos_.y_ + size_.y_), color_, true);
	DrawBox((int)(pos_.x_ - size_.x_ * 2 / 3), (int)(pos_.y_ + size_.y_), (int)(pos_.x_ + size_.x_ * 2 / 3), (int)(pos_.y_ + size_.y_ * 2), color_, true);
}


void Star::Draw(float num)
{
}
