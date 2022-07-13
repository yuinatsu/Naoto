#include <DxLib.h>
#include <string>
#include "BaseScene.h"
#include "../Input/Keyboard.h"
#include "../Input/Pad.h"

BaseScene::BaseScene()
{
	SetDrawScreen(DX_SCREEN_BACK);		// �����I�Ƀo�b�N�o�b�t�@���w��
	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);	// �`���̃T�C�Y���擾����(�o�b�t�@�j
	screenID_ = MakeScreen(screenSize_.x, screenSize_.y, true);		// �X�N���[���̃T�C�Y
	// �R���g���[���[���
	if (GetJoypadNum())
	{
		controller_ = std::make_unique<Pad>();
	}
	else
	{
		controller_ = std::make_unique<Keyboard>();
	}
	mapNum_ = 1;
}

BaseScene::~BaseScene()
{

}

void BaseScene::Draw(float delta)
{
	// screenID�ɑ΂��ĕ`��
	DrawGraph(0, 0, screenID_, true);
}
