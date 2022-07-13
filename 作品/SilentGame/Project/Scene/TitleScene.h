#pragma once
#include "BaseScene.h"


enum class TSELECT
{
    Start,// �Z���N�g�V�[���ɑJ��
    Setting,// �ݒ�
    Suspension,// �Q�[���I��
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
    void DrawOwnScreen(float delta) override;  // �������g��`��
    Scene GetSceneID(void) override { return Scene::Title; };    // �����̓Q�[���V�[��
    bool GetFlag(void) override { return SceneFlag_; };

    int selectType_;
    int StringPos = 500;
    int OffsetY = 400;


    int mapX = 400;
    int mapY = 250;

};

