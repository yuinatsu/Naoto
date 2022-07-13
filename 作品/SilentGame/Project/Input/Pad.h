#pragma once
#include <DxLib.h>
#include "Controller.h"

constexpr int motionRange = 30000;                                  // �X�e�B�b�N�̔�������

class Pad :
    public Controller
{
public:
    Pad();
    ~Pad();
    bool Init(void) override;										// ������
    void Update(double delta) override;								// �X�V Update(deltaTime)
    void StickUpdate(void);											// �X�e�B�b�N�̍X�V
    CntType GetCntType(void) override { return CntType::Pad; };		// �R���g���[���[�^�C�v�̎擾
private:
    XINPUT_STATE input_;											// �R���g���[���[�̏��
    int padCnt_;												    // �����݂�pad�̐�
    int padID_;														// ������padID
};

