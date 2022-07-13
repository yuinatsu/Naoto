#pragma once
#include "BaseScene.h"
#include "../common/Math.h"

enum class RSELECT
{
    Retry,// もう一度挑戦
    Select,// セレクトシーンに遷移
    Title,// タイトルシーン
    Max,
};

class ResultScene :
    public BaseScene
{
public:
    ResultScene();
    ResultScene(int Ndefeats, float eltime);
    ~ResultScene();
private:
    bool Init(void) override;
    uniqueScene Update(float delta, uniqueScene ownScene) override;
    void DrawOwnScreen(float delta) override;  // 自分自身を描画
    Scene GetSceneID(void) override { return Scene::ResultScene; };    // 自分はリザルトシーン
    bool GetFlag(void) override { return SceneFlag_; };
    // 倒した敵の数
    int Ndefeats_;
    // 経過時間
    float elTime_;
    // 順番に評価が出るようにる
    float emTime_;
    // 描画
    int viewID_;
    Math::Vector2 scSize_;
    int selectType_;
    int StringPos = 450;
    int OffsetY = 400;


    int mapX = 400;
    int mapY = 250;
};

