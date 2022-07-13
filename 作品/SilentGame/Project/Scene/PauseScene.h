#pragma once
#include "BaseScene.h"

enum class PSELECT
{
    Resume,// 再開
    Retry,// リトライ
    SelectScene,// セレクトシーンに遷移
    Setting,// 設定
    Suspension,// ゲーム終了
    Max,
};

class PauseScene :
    public BaseScene
{
public:
    PauseScene();
    PauseScene(uniqueScene beforScene);
    ~PauseScene();
private:
    bool Init(void) override;
    uniqueScene Update(float delta, uniqueScene ownScene) override;
    void DrawOwnScreen(float delta) override;  // 自分自身を描画
    Scene GetSceneID(void) override { return Scene::Pause; };    // 自分はポーズシーン
    bool GetFlag(void) override { return SceneFlag_; };

    uniqueScene beforScene_;

    int selectType_;
    int StringPos = 500;
    int OffsetY = 250;


    int mapX = 400;
    int mapY = 250;


};

