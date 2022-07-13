#pragma once
#include "BaseScene.h"
#include "../common/Math.h"

enum class RSELECT
{
    Retry,// ������x����
    Select,// �Z���N�g�V�[���ɑJ��
    Title,// �^�C�g���V�[��
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
    void DrawOwnScreen(float delta) override;  // �������g��`��
    Scene GetSceneID(void) override { return Scene::ResultScene; };    // �����̓��U���g�V�[��
    bool GetFlag(void) override { return SceneFlag_; };
    // �|�����G�̐�
    int Ndefeats_;
    // �o�ߎ���
    float elTime_;
    // ���Ԃɕ]�����o��悤�ɂ�
    float emTime_;
    // �`��
    int viewID_;
    Math::Vector2 scSize_;
    int selectType_;
    int StringPos = 450;
    int OffsetY = 400;


    int mapX = 400;
    int mapY = 250;
};

