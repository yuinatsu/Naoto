#pragma once
#include <memory>
#include "Shape.h"

class Square :
    public Shape
{
public:
	//Square();
	Square(Vector2Flt&& pos, Vector2Flt&& size);// �E�Ӓl�Q�ƁF&&
	~Square();
	void Update(float delta, ShapeVec& shapeVec) override;
	void Draw(void) override;// �}�`�̕`��
	void Draw(float num) override;// �}�`�̕`��(�C�ӂ̃T�C�Y�ύX��)
	void Draw(float num, Vector2Flt offset) override;// �}�`�̕`��(�C�ӂ̃T�C�Y�ύX�A�}�`�̒��S���W)
	ShapeType GetType() override { return ShapeType::Square; };
	Vector2Flt GetPos() override { return pos_; };
	Vector2Flt GetSize() override { return size_; };
	bool isAlive(void) override{ return Alive_; };
	int GetColor() override { return color_; };
private:
	int color_ = 0x00ff00;
	int speed = 200;
};

