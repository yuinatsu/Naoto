#pragma once
#include "BaseScene.h"

enum class SELECT_TYPE
{
    StageOne,
    StageTwo,
    StageThree,
    StageFour,
    //Title,
    Max,
};

class SelectScene :
    public BaseScene
{
public:
    SelectScene();
    ~SelectScene();
private:
    bool Init(void) override;
    uniqueScene Update(float delta, uniqueScene ownScene) override;
    void DrawOwnScreen(float delta) override;                     // 自分自身を描画
    Scene GetSceneID(void) override { return Scene::Select; };    // 自分はセレクトシーン
    bool GetFlag(void) override { return SceneFlag_; };

    int selecterPic_;
    int selecterLPic_;

    int selecterLPos_ = 300;

    bool selecterPicFlag_ = true;
    bool selecterPicLFlag_ = true;
  
    int selectType_;
    int OffsetY = 500;

    int StringPos = 480;
    int TitleStringPos = 800;

    int gameMap_;
    double maxRate_ = 0.95;
    double minRate_ = 0;
    double minRate_stage_two = 0;
    double minRate_stage_three = 0;
    double minRate_stage_four = 0;
    double speed = 0.1;

    int ScreenSizeX = 1060;
    int ScreenSizeY = 660;

    int mapPicPosX = ScreenSizeX / 2;
    int mapPicPosY = ScreenSizeY / 2 - 100;

    int se1;
};