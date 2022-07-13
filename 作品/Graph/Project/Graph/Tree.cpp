#include <dxlib.h>
#include "Tree.h"
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"


Tree::Tree(Vector2Flt&& pos, Vector2Flt&& size) : Shape(pos, size)
{
}


Tree::~Tree()
{
}


void Tree::Update(float delta, ShapeVec& shapeVec)
{
	if (flag1)
	{
		pos_.y_ += speed * delta;
		if (pos_.y_ + (size_.y_ + 15) * 2 >= 768)
		{
			flag1 = false;
			speed = rand() % 300 + 50;
		}
	}
	if (!flag1)
	{
		pos_.y_ -= speed * delta;
		if (pos_.y_ <= 0)
		{
			flag1 = true;
			speed = rand() % 300 + 50;
		}
	}
	if (flag2)
	{
		pos_.x_ += speed * delta;
		if (pos_.x_ + size_.x_ / 2 >= 1024)
		{
			flag2 = false;
			speed = rand() % 300 + 50;
		}
	}
	if (!flag2)
	{
		pos_.x_ -= speed * delta;
		if (pos_.x_ - size_.x_ / 2 <= 0)
		{
			flag2 = true;
			speed = rand() % 300 + 50;
		}
	}
}


void Tree::Draw(void)
{
	DrawTriangle((int)pos_.x_, (int)pos_.y_, (int)(pos_.x_ - (size_.x_ + size_.x_ / 3) / 2), (int)(pos_.y_ + size_.y_ * 2), (int)(pos_.x_ + (size_.x_ + size_.x_ / 3) / 2), (int)(pos_.y_ + size_.y_ * 2), color_, true);
	DrawTriangle((int)pos_.x_, (int)pos_.y_, (int)(pos_.x_ - size_.x_ / 2), (int)(pos_.y_ + size_.y_), (int)(pos_.x_ + size_.x_ / 2), (int)(pos_.y_ + size_.y_), color_, true);
	DrawBox((int)(pos_.x_ - size_.x_ / 3), (int)(pos_.y_ + size_.y_ * 2), (int)(pos_.x_ + size_.x_ / 3), (int)(pos_.y_ + (size_.y_ + 15) * 2), color_, true);
}


void Tree::Draw(float num)
{
}
