#include <dxlib.h>
#include "Square.h"
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"
#include "Circle.h"


Square::Square(Vector2Flt&& pos, Vector2Flt&& size) : Shape(pos, size)// �R���X�g�t���ϐ��̓R���X�g���N�^������O�ɋL�q
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


	// �����蔻��
	for (auto& shape : shapeVec)
	{
		// ��`�Ɖ~
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
				flag = false;//��`�ɉ~�̔��a���𑫂����͈�
			}
			if (pos_.x_ >= cPos.x_ && 
				pos_.y_ >= cPos.y_ && 
				!((pos_.x_ - cPos.x_) * (pos_.x_ - cPos.x_) + (pos_.y_ + cPos.y_) * (pos_.y_ + cPos.y_) <= cSize.x_ * cSize.x_))
			{
				flag = false;//����̓����蔻��
			}
			if (pos_.x_ + size_.x_ <= cPos.x_ && 
				pos_.y_ >= cPos.y_ && 
				!((pos_.x_ + size_.x_ - cPos.x_) * (pos_.x_ + size_.x_ - cPos.x_) + (pos_.y_ + cPos.y_) * (pos_.y_ + cPos.y_) <= cSize.x_ * cSize.x_))
			{
				flag = false;//�E��̓����蔻��
			}
			if (pos_.x_ >= cPos.x_ &&
				pos_.y_ + size_.y_ <= cPos.y_ &&
				!((pos_.x_ - cPos.x_) * (pos_.x_ - cPos.x_) + (pos_.y_ + size_.y_ + cPos.y_) * (pos_.y_ + size_.y_ + cPos.y_) <= cSize.x_ * cSize.x_))
			{
				flag = false;//�����̓����蔻��
			}
			if (pos_.x_ + size_.x_ <= cPos.x_ &&
				pos_.y_ + size_.y_ <= cPos.y_ &&
				!((pos_.x_ + size_.x_ - cPos.x_) * (pos_.x_ + size_.x_ - cPos.x_) + (pos_.y_ + size_.y_ + cPos.y_) * (pos_.y_ + size_.y_ + cPos.y_) <= cSize.x_ * cSize.x_))
			{
				flag = false;//�E���̓����蔻��
			}

			// �����������̏���
			if (flag)
			{
				color_ = 0x00ffff;
			}
		}
		// ��`�ƎO�p
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
				flag = false;//��`�ɉ~�̔��a���𑫂����͈�
			}
			if (pos_.x_ >= tPos.x_ &&
				pos_.y_ >= tPos.y_ &&
				!((pos_.x_ - tPos.x_) * (pos_.x_ - tPos.x_) + (pos_.y_ + tPos.y_) * (pos_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//����̓����蔻��
			}
			if (pos_.x_ + size_.x_ <= tPos.x_ &&
				pos_.y_ >= tPos.y_ &&
				!((pos_.x_ + size_.x_ - tPos.x_) * (pos_.x_ + size_.x_ - tPos.x_) + (pos_.y_ + tPos.y_) * (pos_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//�E��̓����蔻��
			}
			if (pos_.x_ >= tPos.x_ &&
				pos_.y_ + size_.y_ <= tPos.y_ &&
				!((pos_.x_ - tPos.x_) * (pos_.x_ - tPos.x_) + (pos_.y_ + size_.y_ + tPos.y_) * (pos_.y_ + size_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//�����̓����蔻��
			}
			if (pos_.x_ + size_.x_ <= tPos.x_ &&
				pos_.y_ + size_.y_ <= tPos.y_ &&
				!((pos_.x_ + size_.x_ - tPos.x_) * (pos_.x_ + size_.x_ - tPos.x_) + (pos_.y_ + size_.y_ + tPos.y_) * (pos_.y_ + size_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//�E���̓����蔻��
			}

			// �����������̏���
			if (flag)
			{
				color_ = 0xff00ff;
			}
		}
		// ��`�ƃc���[
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
		// ��`�ƃ~�b�Z�[
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
				flag = false;//��`�ɉ~�̔��a���𑫂����͈�
			}
			if (pos_.x_ >= tPos.x_ &&
				pos_.y_ >= tPos.y_ &&
				!((pos_.x_ - tPos.x_) * (pos_.x_ - tPos.x_) + (pos_.y_ + tPos.y_) * (pos_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//����̓����蔻��
			}
			if (pos_.x_ + size_.x_ <= tPos.x_ &&
				pos_.y_ >= tPos.y_ &&
				!((pos_.x_ + size_.x_ - tPos.x_) * (pos_.x_ + size_.x_ - tPos.x_) + (pos_.y_ + tPos.y_) * (pos_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//�E��̓����蔻��
			}
			if (pos_.x_ >= tPos.x_ &&
				pos_.y_ + size_.y_ <= tPos.y_ &&
				!((pos_.x_ - tPos.x_) * (pos_.x_ - tPos.x_) + (pos_.y_ + size_.y_ + tPos.y_) * (pos_.y_ + size_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//�����̓����蔻��
			}
			if (pos_.x_ + size_.x_ <= tPos.x_ &&
				pos_.y_ + size_.y_ <= tPos.y_ &&
				!((pos_.x_ + size_.x_ - tPos.x_) * (pos_.x_ + size_.x_ - tPos.x_) + (pos_.y_ + size_.y_ + tPos.y_) * (pos_.y_ + size_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//�E���̓����蔻��
			}

			// �����������̏���
			if (flag)
			{
				color_ = 0x0000ff;
				auto scrSize = Vector2Flt{ 1024 - size_.x_,768 - size_.y_ };
				pos_.x_ = rand() % (int)scrSize.x_;
				pos_.y_ = rand() % (int)scrSize.y_;
			}
		}
		// ��`�Ɖ�
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
				flag = false;//��`�ɉ~�̔��a���𑫂����͈�
			}
			if (pos_.x_ >= tPos.x_ &&
				pos_.y_ >= tPos.y_ &&
				!((pos_.x_ - tPos.x_) * (pos_.x_ - tPos.x_) + (pos_.y_ + tPos.y_) * (pos_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//����̓����蔻��
			}
			if (pos_.x_ + size_.x_ <= tPos.x_ &&
				pos_.y_ >= tPos.y_ &&
				!((pos_.x_ + size_.x_ - tPos.x_) * (pos_.x_ + size_.x_ - tPos.x_) + (pos_.y_ + tPos.y_) * (pos_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//�E��̓����蔻��
			}
			if (pos_.x_ >= tPos.x_ &&
				pos_.y_ + size_.y_ <= tPos.y_ &&
				!((pos_.x_ - tPos.x_) * (pos_.x_ - tPos.x_) + (pos_.y_ + size_.y_ + tPos.y_) * (pos_.y_ + size_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//�����̓����蔻��
			}
			if (pos_.x_ + size_.x_ <= tPos.x_ &&
				pos_.y_ + size_.y_ <= tPos.y_ &&
				!((pos_.x_ + size_.x_ - tPos.x_) * (pos_.x_ + size_.x_ - tPos.x_) + (pos_.y_ + size_.y_ + tPos.y_) * (pos_.y_ + size_.y_ + tPos.y_) <= tSize.x_ * tSize.x_))
			{
				flag = false;//�E���̓����蔻��
			}

			// �����������̏���
			if (flag)
			{
				color_ = tColor;
			}
		}
	}

	/*_dbgDrawFormatString(0, 0, 0xffffff, "�o�ߎ��� : %f", deltaSum);
	_dbgDrawFormatString(0, 16, 0xffffff, "�ړ����� : %f", moveAve);*/

	//moveSum += 100 * delta;
	//_dbgDrawFormatString(0, 32, 0xffffff, "�ړ����� : %f", moveSum);
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
