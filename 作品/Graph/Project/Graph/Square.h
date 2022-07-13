#pragma once
#include <memory>
#include "Shape.h"

class Square :
    public Shape
{
public:
	//Square();
	Square(Vector2Flt&& pos, Vector2Flt&& size);// 右辺値参照：&&
	~Square();
	void Update(float delta, ShapeVec& shapeVec) override;
	void Draw(void) override;// 図形の描画
	void Draw(float num) override;// 図形の描画(任意のサイズ変更可)
	void Draw(float num, Vector2Flt offset) override;// 図形の描画(任意のサイズ変更可、図形の中心座標)
	ShapeType GetType() override { return ShapeType::Square; };
	Vector2Flt GetPos() override { return pos_; };
	Vector2Flt GetSize() override { return size_; };
	bool isAlive(void) override{ return Alive_; };
	int GetColor() override { return color_; };
private:
	int color_ = 0x00ff00;
	int speed = 200;
};

