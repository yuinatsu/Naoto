#include <dxlib.h>
#include "Square.h"
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"
#include "Circle.h"


Square::Square(Vector2Flt&& pos, Vector2Flt&& size) : Shape(pos, size)// コンスト付き変数はコンストラクタが走る前に記述
{
}


Square::~Square()
{
}


void Square::Update(float delta, ShapeVec& shapeVec)
{
	static float moveSum = 0.0f;
	static float moveAve = 0.0f;
	static float deltaSum = 0.0f;
	static int sec = 0;
	deltaSum += delta;
	if ((int)deltaSum > sec)
	{
		sec = (int)deltaSum;
		moveAve = moveSum / sec;
	}
	if (flag1)
	{
		pos_.x_ += speed * delta;
		if (pos_.x_ + size_.x_ >= 1024)
		{
			flag1 = false;
		}
	}
	if (!flag1)
	{
		pos_.x_ -= speed * delta;
		if (pos_.x_ <= 0)
		{
			flag1 = true;
		}
	}
	if (flag2)
	{
		pos_.y_ += speed * 2 * delta;
		if (pos_.y_ + size_.y_ >= 768)
		{
			flag2 = false;
		}
	}
	if (!flag2)
	{
		pos_.y_ -= speed * 2 * delta;
		if (pos_.y_ <= 0)
		{
			flag2 = true;
		}
	}


	// 当たり判定
	for (auto& shape : shapeVec)
	{
		// 矩形と円
		if (shape->GetType() == ShapeType::Circle)
		{
			auto cPos = shape->GetPos();
			auto cSize = shape->GetSize();

			bool flag = true;
			if (pos_.x_ - cSize.x_ >= cPos.x_ || 
				pos_.x_ + size_.x_ + cSize.x_ <= cPos.x_ || 
				pos_.y_ - cSize.y_ >= cPos.y_ || 
				pos_.y_ + size_.y_ + cSize.y_ <= cPos.y_)
			{
				flag = false;//矩形に円の半径分を足した範囲
			}
			if (pos_.x_ >= cPos.x_ && 
				pos_.y_ >= cPos.y_ && 
				!((pos_.x_ - cPos.x_) * (pos_.x_ - cPos.x_) + (pos_.y_ + cPos.y_) * (pos_.y_ + cPos.y_) <= cSize.x_ * cSize.x_))
			{
				flag = false;//左上の当たり判定
			}
			if (pos_.x_ + size_.x_ <= cPos.x_ && 
				pos_.y_ >= cPos.y_ && 
				!((pos_.x_ + size_.x_ - cPos.x_) * (pos_.x_ + size_.x_ - cPos.x_) + (pos_.y_ + cPos.y_) * (pos_.y_ + cPos.y_) <= cSize.x_ * cSize.x_))
			{
				flag = false;//右上の当たり判定
			}
			if (pos_.x_ >= cPos.x_ &&
				pos_.y_ + size_.y_ <= cPos.y_ &&
				!((pos_.x_ - cPos.x_) * (pos_.x_ - cPos.x_) + (pos_.y_ + size_.y_ + cPos.y_) * (pos_.y_ + size_.y_ + cPos.y_) <= cSize.x_ * cSize.x_))
			{
				flag = false;//左下の当たり判定
			}
			if (pos_.x_ + size_.x_ <= cPos.x_ &&
				pos_.y_ + size_.y_ <= cPos.y_ &&
				!((pos_.x_ + size_.x_ - cPos.x_) * (pos_.x_ + size_.x_ - cPos.x_) + (pos_.y_ + size_.y_ + cPos.y_) * (pos_.y_ + size_.y_ + cPos.y_) <= cSize.x_ * cSize.x_))
			{
				flag = false;//右下の当たり判定
			}

			// 当たった時の処理
			if (flag)
			{
				color_ = 0x00ffff;
			}
		}
		// 矩形と三角
		if (shape->GetType() == ShapeType::Triangle)
		{
			auto tPos = shape->GetPos();
			auto tSize = shape->GetSize();

			bool flag = true;
			if (pos_.x_ - tSize.x_ >= tPos.x_ ||
				pos_.x_ + size_.x_ + tSize.x_ <= tPos.x_ ||
				pos_.y_ - tSize.y_ >= tPos.y_ ||
				pos_.y_ + size_.y_ + tSize.y_ <= tPos.y_)
			{
				flag = false;//矩形に円の半径分を足した範囲
			}
			if (pos_.x_ >= tPos.x_ &&
				pos_.y_ >= tPos.y_ &&
				!((pos_.x_ - tPos.x_) * (pos_.x_ - tPos.x_) + (pos_.y_ + tPos.y_) * (pos_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//左上の当たり判定
			}
			if (pos_.x_ + size_.x_ <= tPos.x_ &&
				pos_.y_ >= tPos.y_ &&
				!((pos_.x_ + size_.x_ - tPos.x_) * (pos_.x_ + size_.x_ - tPos.x_) + (pos_.y_ + tPos.y_) * (pos_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//右上の当たり判定
			}
			if (pos_.x_ >= tPos.x_ &&
				pos_.y_ + size_.y_ <= tPos.y_ &&
				!((pos_.x_ - tPos.x_) * (pos_.x_ - tPos.x_) + (pos_.y_ + size_.y_ + tPos.y_) * (pos_.y_ + size_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//左下の当たり判定
			}
			if (pos_.x_ + size_.x_ <= tPos.x_ &&
				pos_.y_ + size_.y_ <= tPos.y_ &&
				!((pos_.x_ + size_.x_ - tPos.x_) * (pos_.x_ + size_.x_ - tPos.x_) + (pos_.y_ + size_.y_ + tPos.y_) * (pos_.y_ + size_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//右下の当たり判定
			}

			// 当たった時の処理
			if (flag)
			{
				color_ = 0xff00ff;
			}
		}
		// 矩形とツリー
		if (shape->GetType() == ShapeType::Tree)
		{
			auto tSize = shape->GetSize();
			auto tPos = shape->GetPos();

			if (pos_.x_ <= tPos.x_ + tSize.x_ * 2 / 3 && 
				pos_.x_ + size_.x_ >= tPos.x_ - tSize.x_ / 3 && 
				pos_.y_ <= tPos.y_ + (tSize.y_ + 15) * 2 &&
				pos_.y_ + size_.y_ >= tPos.y_)
			{
				color_ = 0xffff00;
			}
		}
		// 矩形とミッ〇ー
		if (shape->GetType() == ShapeType::Micky)
		{
			auto tPos = shape->GetPos();
			auto tSize = shape->GetSize();
			tSize *= Vector2Flt{ 1.5,1.5 };

			bool flag = true;
			if (pos_.x_ - tSize.x_ >= tPos.x_ ||
				pos_.x_ + size_.x_ + tSize.x_ <= tPos.x_ ||
				pos_.y_ - tSize.y_ >= tPos.y_ ||
				pos_.y_ + size_.y_ + tSize.y_ <= tPos.y_)
			{
				flag = false;//矩形に円の半径分を足した範囲
			}
			if (pos_.x_ >= tPos.x_ &&
				pos_.y_ >= tPos.y_ &&
				!((pos_.x_ - tPos.x_) * (pos_.x_ - tPos.x_) + (pos_.y_ + tPos.y_) * (pos_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//左上の当たり判定
			}
			if (pos_.x_ + size_.x_ <= tPos.x_ &&
				pos_.y_ >= tPos.y_ &&
				!((pos_.x_ + size_.x_ - tPos.x_) * (pos_.x_ + size_.x_ - tPos.x_) + (pos_.y_ + tPos.y_) * (pos_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//右上の当たり判定
			}
			if (pos_.x_ >= tPos.x_ &&
				pos_.y_ + size_.y_ <= tPos.y_ &&
				!((pos_.x_ - tPos.x_) * (pos_.x_ - tPos.x_) + (pos_.y_ + size_.y_ + tPos.y_) * (pos_.y_ + size_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//左下の当たり判定
			}
			if (pos_.x_ + size_.x_ <= tPos.x_ &&
				pos_.y_ + size_.y_ <= tPos.y_ &&
				!((pos_.x_ + size_.x_ - tPos.x_) * (pos_.x_ + size_.x_ - tPos.x_) + (pos_.y_ + size_.y_ + tPos.y_) * (pos_.y_ + size_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//右下の当たり判定
			}

			// 当たった時の処理
			if (flag)
			{
				color_ = 0x0000ff;
				auto scrSize = Vector2Flt{ 1024 - size_.x_,768 - size_.y_ };
				pos_.x_ = rand() % (int)scrSize.x_;
				pos_.y_ = rand() % (int)scrSize.y_;
			}
		}
		// 矩形と家
		if (shape->GetType() == ShapeType::Star)
		{
			auto tPos = shape->GetPos();
			auto tSize = shape->GetSize();
			auto tColor = shape->GetColor();
			tPos.y_ += tSize.y_;

			bool flag = true;
			if (pos_.x_ - tSize.x_ >= tPos.x_ ||
				pos_.x_ + size_.x_ + tSize.x_ <= tPos.x_ ||
				pos_.y_ - tSize.y_ >= tPos.y_ ||
				pos_.y_ + size_.y_ + tSize.y_ <= tPos.y_)
			{
				flag = false;//矩形に円の半径分を足した範囲
			}
			if (pos_.x_ >= tPos.x_ &&
				pos_.y_ >= tPos.y_ &&
				!((pos_.x_ - tPos.x_) * (pos_.x_ - tPos.x_) + (pos_.y_ + tPos.y_) * (pos_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//左上の当たり判定
			}
			if (pos_.x_ + size_.x_ <= tPos.x_ &&
				pos_.y_ >= tPos.y_ &&
				!((pos_.x_ + size_.x_ - tPos.x_) * (pos_.x_ + size_.x_ - tPos.x_) + (pos_.y_ + tPos.y_) * (pos_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//右上の当たり判定
			}
			if (pos_.x_ >= tPos.x_ &&
				pos_.y_ + size_.y_ <= tPos.y_ &&
				!((pos_.x_ - tPos.x_) * (pos_.x_ - tPos.x_) + (pos_.y_ + size_.y_ + tPos.y_) * (pos_.y_ + size_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//左下の当たり判定
			}
			if (pos_.x_ + size_.x_ <= tPos.x_ &&
				pos_.y_ + size_.y_ <= tPos.y_ &&
				!((pos_.x_ + size_.x_ - tPos.x_) * (pos_.x_ + size_.x_ - tPos.x_) + (pos_.y_ + size_.y_ + tPos.y_) * (pos_.y_ + size_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//右下の当たり判定
			}

			// 当たった時の処理
			if (flag)
			{
				color_ = tColor;
			}
		}
	}

	/*_dbgDrawFormatString(0, 0, 0xffffff, "経過時間 : %f", deltaSum);
	_dbgDrawFormatString(0, 16, 0xffffff, "移動平均 : %f", moveAve);*/

	//moveSum += 100 * delta;
	//_dbgDrawFormatString(0, 32, 0xffffff, "移動総量 : %f", moveSum);
}


void Square::Draw(void)
{
	DrawBox((int)pos_.x_, (int)pos_.y_, (int)(pos_.x_ + size_.x_), (int)(pos_.y_ + size_.y_), color_, true);
}


void Square::Draw(float num)
{
	DrawBox((int)pos_.x_, (int)pos_.y_, (int)(pos_.x_ + size_.x_ * num), (int)(pos_.y_ + size_.y_ * num), color_, true);
}


void Square::Draw(float num, Vector2Flt offset)
{
	//Vector2 pos{ (int)(pos_.x_ + offset.x_ - size_.x_ * num * (offset.x_ / (float)size_.x_)),(int)(pos_.y_ + offset.y_ - size_.y_ * num * (offset.y_ / (float)size_.y_)) };// (offset / (float)size_) ... 0.5
	Vector2Flt pos{ pos_ + offset - size_ * num * offset / size_ };
	DrawBox((int)pos.x_, (int)pos.y_, (int)(pos.x_ + size_.x_ * num), (int)(pos.y_ + size_.y_ * num), color_, true);
}
