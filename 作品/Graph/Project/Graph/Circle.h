#pragma once
#include "Shape.h"

class Circle :
    public Shape
{
public:
    Circle(Vector2Flt&& pos, Vector2Flt&& size);
    ~Circle();
    void Update(float delta, ShapeVec& shapeVec) override;
    void Draw(void) override;
    void Draw(float num) override;
    void Draw(float num, Vector2Flt offset) override {};
    ShapeType GetType() override { return ShapeType::Circle; };
    Vector2Flt GetPos() override { return pos_; };
    Vector2Flt GetSize() override{ return size_; };
    bool isAlive(void) override { return Alive_; };
    int GetColor() override { return color_; };
private:
    int color_ = 0x00ffff;
    int speed = 300;
};

