#pragma once
#include "Shape.h"

class Tree :
    public Shape
{
public:
    Tree(Vector2Flt&& pos, Vector2Flt&& size);
    ~Tree();
    void Update(float delta, ShapeVec& shapeVec) override;
    void Draw(void);
    void Draw(float num) override;// 図形の描画(任意のサイズ変更可)
    void Draw(float num, Vector2Flt offset) override {};// 図形の描画(任意のサイズ変更可、図形の中心座標)
    ShapeType GetType() override { return ShapeType::Tree; };
    Vector2Flt GetPos() override { return pos_; };
    Vector2Flt GetSize() override { return size_; };
    bool isAlive(void) override { return Alive_; };
    int GetColor() override { return color_; };
private:
    int color_ = 0x00ff00;
    int speed = 100;
};

