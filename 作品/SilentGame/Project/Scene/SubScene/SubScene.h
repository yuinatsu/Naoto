#pragma once
#include "../BaseScene.h"

// ���j���[���Ɏg���N���X
class SubScene :
    public BaseScene
{
public:
    SubScene();
    SubScene(uniqueScene owner);
    virtual ~SubScene();

private:

    // �Ăяo����
    uniqueScene owner_;
};

