#include "SceneMng.h"
#include <DxLib.h>
#include "../_debug/_DebugDispOut.h"
#include "../_debug/_DebugConOut.h"
#include "EditScene.h"
#include "GameScene.h"


void SceneMng::Init()
{
	SysInit();			// �d�v�ȓ��e���������܂�Ă���̂ŃR���X�g���N�^���ɏ����Ă��悢
	//uniqueBaseScene scene_ = std::make_unique<EditScene>();
	//scene_.reset(new GameScene());				// ���Z�b�g�V�[��		�X�}�[�g�|�C���^
	scene_ = std::make_unique<EditScene>();
}


void SceneMng::Run()
{
	Init();

	// �Q�[�����[�v
	//---------------
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//_dbgStartDraw();

		scene_ = scene_->Update(std::move(scene_));					// std::move ... �i�j���̂��̂��ړ�
		//(*scene_).Update();				// �A�X�^���X�N���h�b�g�̕����D��x�������̂ŃJ�b�R��t����

		Draw();
	}
}


void SceneMng::Draw()
{
	SetDrawScreen(DX_SCREEN_BACK);			// �`�悷���ʂ𗠂̉�ʂɐݒ�
	ClearDrawScreen();						// �`�悵����ʂ��N���A

	scene_->Draw();

	_dbgAddDraw();

	ScreenFlip();
}


// �V�X�e���n������
//-------------------
bool SceneMng::SysInit()
{
	// �V�X�e������
	//-------------------
	SetWindowText("���[�h�����i�[");				// �Q�[���E�B���h�E�̃^�C�g��
	SetGraphMode(scnArea_.x, scnArea_.y, 16);				// �Q�[���E�B���h�E�̃T�C�Y�ƐF���[�h��ݒ�
	ChangeWindowMode(true);									// �Q�[���E�B���h�E�̕\�����@ (true : window   false : �t���X�N���[��)

	if (DxLib_Init() == -1)									// DX���C�u�����̏���������
	{
		TRACE("DxLib �̏��������s");
		return false;										// DX���C�u�����̏��������s�̈׃V�X�e���I��
	}

	SetDrawScreen(DX_SCREEN_BACK);							
	_dbgSetup(scnArea_.x, scnArea_.y, 255);

	return true;
}


#define VIEW_AREA_X 21
#define VIEW_AREA_Y 17


SceneMng::SceneMng() : scnArea_{ 800,600 }, worldArea_{ VIEW_AREA_X * 2,VIEW_AREA_Y }, viewArea_{ VIEW_AREA_X,VIEW_AREA_Y }, chipSize_{ 32,32 }, drawOffset_{ (scnArea_ - (viewArea_ * chipSize_)) / 2 }					// �X�N���[���G���A�T�C�Y��`
{

}


SceneMng::~SceneMng()
{

}
