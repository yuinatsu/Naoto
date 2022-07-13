#pragma once
#include "../BaseScene.h"

// メニュー等に使うクラス
class SubScene :
    public BaseScene
{
public:
    SubScene();
    SubScene(uniqueScene owner);
    virtual ~SubScene();

private:

    // 呼び出し元
    uniqueScene owner_;
};

