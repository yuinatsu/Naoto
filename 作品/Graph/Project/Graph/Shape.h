#pragma once
#include <memory>
#include <vector>
#include "Vector2.h"

enum class ShapeType
{
	Square,
	Circle,
	Triangle,
	Star,
	Tree,
	Micky,
	Max
};

class Shape;
using ShapeVec = std::vector<std::unique_ptr<Shape>>;


class Shape
{
public:
	Shape(Vector2Flt& pos, Vector2Flt& size);
	~Shape();
	virtual void Update(float delta, ShapeVec& shapeVec) = 0;
	virtual void Draw(void) = 0;
	virtual void Draw(float num) = 0;
	virtual void Draw(float num, Vector2Flt offset) {};// = 0; ... アドレスなし(純粋仮想関数
	virtual ShapeType GetType() = 0;
	virtual Vector2Flt GetPos() = 0;
	virtual Vector2Flt GetSize() = 0;
	virtual bool isAlive(void) = 0;
	virtual int GetColor() = 0;

	Vector2Flt pos_;
	Vector2Flt size_;

	std::unique_ptr<Shape> shape_;
private:
protected:
	bool flag1 = true;
	bool flag2 = true;
	bool Alive_ = true;
};
