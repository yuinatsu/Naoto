#include <dxlib.h>
#include "Triangle.h"
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"


Triangle::Triangle(Vector2Flt&& pos, Vector2Flt&& size) : Shape(pos, size)
{
}


Triangle::~Triangle()
{
}


void Triangle::Update(float delta, ShapeVec& shapeVec)
{
	if (flag1)
	{
		pos_.x_ += speed * delta;
		if (pos_.x_ + size_.x_ / 2 >= 1024)
		{
			flag1 = false;
		}
	}
	if (!flag1)
	{
		pos_.x_ -= speed * delta;
		if (pos_.x_ - size_.x_ / 2 <= 0)
		{
			flag1 = true;
		}
	}
	if (flag2)
	{
		pos_.y_ += (speed / 3) * delta;
		if (pos_.y_ + size_.y_ >= 768)
		{
			flag2 = false;
		}
	}
	if (!flag2)
	{
		pos_.y_ -= (speed / 3) * delta;
		if (pos_.y_ <= 0)
		{
			flag2 = true;
			;
		}
	}

	// 当たり判定
	for (auto& shape : shapeVec)
	{
		// 三角形と矩形
		if (shape->GetType() == ShapeType::Square)
		{
			auto sPos = shape->GetPos();
			auto sSize = shape->GetSize();

			bool flag = true;
			if (sPos.x_ - size_.x_ >= pos_.x_ ||
				sPos.x_ + sSize.x_ + size_.x_ <= pos_.x_ ||
				sPos.y_ - size_.y_ >= pos_.y_ ||
				sPos.y_ + sSize.y_ + size_.y_ <= pos_.y_)
			{
				flag = false;//矩形に円の半径分を足した範囲
			}
			if (sPos.x_ >= pos_.x_ &&
				sPos.y_ >= pos_.y_ &&
				!((sPos.x_ - pos_.x_) * (sPos.x_ - pos_.x_) + (sPos.y_ + pos_.y_) * (sPos.y_ + pos_.y_) <= size_.x_ * size_.x_))
			{
				flag = false;//左上の当たり判定
			}
			if (sPos.x_ + sSize.x_ <= pos_.x_ &&
				sPos.y_ >= pos_.y_ &&
				!((sPos.x_ + sSize.x_ - pos_.x_) * (sPos.x_ + sSize.x_ - pos_.x_) + (sPos.y_ + pos_.y_) * (sPos.y_ + pos_.y_) <= size_.x_ * size_.x_))
			{
				flag = false;//右上の当たり判定
			}
			if (sPos.x_ >= pos_.x_ &&
				sPos.y_ + sSize.y_ <= pos_.y_ &&
				!((sPos.x_ - pos_.x_) * (sPos.x_ - pos_.x_) + (sPos.y_ + sSize.y_ + pos_.y_) * (sPos.y_ + sSize.y_ + pos_.y_) <= size_.x_ * size_.x_))
			{
				flag = false;//左下の当たり判定
			}
			if (sPos.x_ + sSize.x_ <= pos_.x_ &&
				sPos.y_ + sSize.y_ <= pos_.y_ &&
				!((sPos.x_ + sSize.x_ - pos_.x_) * (sPos.x_ + sSize.x_ - pos_.x_) + (sPos.y_ + sSize.y_ + pos_.y_) * (sPos.y_ + sSize.y_ + pos_.y_) <= size_.x_ * size_.x_))
			{
				flag = false;//右下の当たり判定
			}

			// 当たった時の処理
			if (flag)
			{
				speed += 10;
			}
		}
		// 三角形と円
		if (shape->GetType() == ShapeType::Circle)
		{
			auto sPos = shape->GetPos();
			auto sSize = shape->GetSize();

			auto diff = sPos - pos_;
			auto totalRad = sSize + size_;
			if (totalRad.x_ * totalRad.x_ >= diff.x_ * diff.x_ + diff.y_ * diff.y_)
			{
				speed -= 10;
				if (speed < 1)
				{
					speed = 0;
				}
			}
		}
		// 三角形とツリー
		if (shape->GetType() == ShapeType::Tree)
		{
			auto sPos = shape->GetPos();
			auto sSize = shape->GetSize();

			sSize.y_ = (size_.y_ + 15) * 2;

			bool flag = true;
			if (sPos.x_ - size_.x_ >= pos_.x_ ||
				sPos.x_ + sSize.x_ + size_.x_ <= pos_.x_ ||
				sPos.y_ - size_.y_ >= pos_.y_ ||
				sPos.y_ + sSize.y_ + size_.y_ <= pos_.y_)
			{
				flag = false;//矩形に円の半径分を足した範囲
			}
			if (sPos.x_ >= pos_.x_ &&
				sPos.y_ >= pos_.y_ &&
				!((sPos.x_ - pos_.x_) * (sPos.x_ - pos_.x_) + (sPos.y_ + pos_.y_) * (sPos.y_ + pos_.y_) <= size_.x_ * size_.x_))
			{
				flag = false;//左上の当たり判定
			}
			if (sPos.x_ + sSize.x_ <= pos_.x_ &&
				sPos.y_ >= pos_.y_ &&
				!((sPos.x_ + sSize.x_ - pos_.x_) * (sPos.x_ + sSize.x_ - pos_.x_) + (sPos.y_ + pos_.y_) * (sPos.y_ + pos_.y_) <= size_.x_ * size_.x_))
			{
				flag = false;//右上の当たり判定
			}
			if (sPos.x_ >= pos_.x_ &&
				sPos.y_ + sSize.y_ <= pos_.y_ &&
				!((sPos.x_ - pos_.x_) * (sPos.x_ - pos_.x_) + (sPos.y_ + sSize.y_ + pos_.y_) * (sPos.y_ + sSize.y_ + pos_.y_) <= size_.x_ * size_.x_))
			{
				flag = false;//左下の当たり判定
			}
			if (sPos.x_ + sSize.x_ <= pos_.x_ &&
				sPos.y_ + sSize.y_ <= pos_.y_ &&
				!((sPos.x_ + sSize.x_ - pos_.x_) * (sPos.x_ + sSize.x_ - pos_.x_) + (sPos.y_ + sSize.y_ + pos_.y_) * (sPos.y_ + sSize.y_ + pos_.y_) <= size_.x_ * size_.x_))
			{
				flag = false;//右下の当たり判定
			}

			// 当たった時の処理
			if (flag)
			{
				speed += 10;
			}
		}
		// 三角形とミッ〇ー
		if (shape->GetType() == ShapeType::Micky)
		{
			auto sPos = shape->GetPos();
			auto sSize = shape->GetSize();
			sSize *= Vector2Flt{ 1.5,1.5 };

			auto diff = sPos - pos_;
			auto totalRad = sSize + size_;
			if (totalRad.x_ * totalRad.x_ >= diff.x_ * diff.x_ + diff.y_ * diff.y_)
			{
				speed -= 10;
				auto scrSize = Vector2Flt{ 1024 - size_.x_,768 - size_.y_ };
				pos_.x_ = rand() % (int)scrSize.x_;
				pos_.y_ = rand() % (int)scrSize.y_;
			}
		}
		// 三角形と家
		if (shape->GetType() == ShapeType::Star)
		{
			auto sPos = shape->GetPos();
			auto sSize = shape->GetSize();
			auto tColor = shape->GetColor();
			sPos.y_ += sSize.y_;

			auto diff = sPos - pos_;
			auto totalRad = sSize + size_;
			if (totalRad.x_ * totalRad.x_ >= diff.x_ * diff.x_ + diff.y_ * diff.y_)
			{
				speed += 10;
				color_ = tColor;
			}
		}
	}
}


void Triangle::Draw(void)
{
	DrawTriangle((int)pos_.x_, (int)pos_.y_, (int)(pos_.x_ - size_.x_ / 2), (int)(pos_.y_ + size_.y_), (int)(pos_.x_ + size_.x_ / 2), (int)(pos_.y_ + size_.y_), color_, true);
}


void Triangle::Draw(float num)
{
	DrawTriangle((int)pos_.x_, (int)pos_.y_, (int)(pos_.x_ - (size_.x_ * num) / 2), (int)(pos_.y_ + size_.y_ * num), (int)(pos_.x_ + (size_.x_ * num) / 2), (int)(pos_.y_ + size_.y_ * num), color_, true);
}
