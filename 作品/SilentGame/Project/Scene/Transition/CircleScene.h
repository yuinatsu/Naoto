#pragma once
#include "TransitionScene.h"
class CircleScene :
    public TransitionScene
{
public:
    CircleScene(double limitTime, uniqueScene beforScene, uniqueScene afterScene);
    ~CircleScene();
private:
    double limitTime_;

    bool UpdataTransition(double delta);
    void DrawOwnScreen(float delta) override;

    int DrawReversalCircle(int x, int y, int r, int Color);
};

