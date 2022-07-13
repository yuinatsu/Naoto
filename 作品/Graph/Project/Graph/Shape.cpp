#include <dxlib.h>
#include "Shape.h"
#include "Circle.h"


Shape::Shape(Vector2Flt& pos, Vector2Flt& size) : pos_(pos), size_(size)
{
	//pos_ = pos_;
	//size_ = size;

	//int num[5];// �Z�}���e�B�N�X
	//num[2] = 5;// �V���^�b�N�X
	//*(num + 2) = 5;// �V���^�b�N�X
}


Shape::~Shape()
{
}


void Shape::Draw(void)
{
	DrawBox((int)pos_.x_, (int)pos_.y_, (int)pos_.x_ + (int)size_.x_, (int)pos_.y_ + (int)size_.y_, 0x00ffff, true);
}
