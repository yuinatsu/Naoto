#pragma once
#include "BaseScene.h"

enum class PSELECT
{
    Resume,// �ĊJ
    Retry,// ���g���C
    SelectScene,// �Z���N�g�V�[���ɑJ��
    Setting,// �ݒ�
    Suspension,// �Q�[���I��
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
    void DrawOwnScreen(float delta) override;  // �������g��`��
    Scene GetSceneID(void) override { return Scene::Pause; };    // �����̓|�[�Y�V�[��
    bool GetFlag(void) override { return SceneFlag_; };

    uniqueScene beforScene_;

    int selectType_;
    int StringPos = 500;
    int OffsetY = 250;


    int mapX = 400;
    int mapY = 250;


};

