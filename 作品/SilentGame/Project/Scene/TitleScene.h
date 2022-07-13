#pragma once
#include "BaseScene.h"


enum class TSELECT
{
    Start,// セレクトシーンに遷移
    Setting,// 設定
    Suspension,// ゲーム終了
    Max,
};

class TitleScene :
    public BaseScene
{
public:
    TitleScene();
    ~TitleScene();
private:
    bool Init(void) override;
    uniqueScene Update(float delta, uniqueScene ownScene) override;
    void DrawOwnScreen(float delta) override;  // 自分自身を描画
    Scene GetSceneID(void) override { return Scene::Title; };    // 自分はゲームシーン
    bool GetFlag(void) override { return SceneFlag_; };

    int selectType_;
    int StringPos = 500;
    int OffsetY = 400;


    int mapX = 400;
    int mapY = 250;

};

