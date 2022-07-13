#pragma once
#include "TransitionScene.h"
class FadeTrans :
    public TransitionScene
{
public:
    FadeTrans(double limitTime, uniqueScene beforScene, uniqueScene afterScene);
    ~FadeTrans();
private:
    double limitTime_;

    bool UpdataTransition(double delta);
    void DrawOwnScreen(float delta) override;
};

