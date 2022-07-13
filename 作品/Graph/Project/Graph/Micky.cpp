#include <dxlib.h>
#include "Micky.h"
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"


Micky::Micky(Vector2Flt&& pos, Vector2Flt&& size) : Shape(pos, size)
{
}


Micky::~Micky()
{
}


void Micky::Update(float delta, ShapeVec& shapeVec)
{
}


void Micky::Draw(void)
{
	DrawCircle((int)(pos_.x_ + size_.x_), (int)(pos_.y_ - size_.x_), (int)(size_.x_ * 2 / 3), color_, true);
	DrawCircle((int)(pos_.x_ - size_.x_), (int)(pos_.y_ - size_.x_), (int)(size_.x_ * 2 / 3), color_, true);
	DrawCircle((int)pos_.x_, (int)pos_.y_, (int)size_.x_, color_, true);
	DrawBox((int)(pos_.x_ - size_.x_ * 3 / 2), (int)(pos_.y_ - size_.x_ / 4), (int)(pos_.x_ + size_.x_ * 3 / 2), (int)(pos_.y_ + size_.x_ / 4), 0xffffff, true);
}


void Micky::Draw(float num)
{
}
