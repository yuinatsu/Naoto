#include <DxLib.h>
#include "GameScene.h"
#include "PauseScene.h"
#include "SelectScene.h"

PauseScene::PauseScene()
{
	Init();
	DrawOwnScreen(0.0);
}

PauseScene::PauseScene(uniqueScene beforScene)
{
	beforScene_ = std::move(beforScene);
	Init();
	DrawOwnScreen(0.0);
}

PauseScene::~PauseScene()
{
}

bool PauseScene::Init(void)
{
	SceneFlag_ = false;
	return true;
}

uniqueScene PauseScene::Update(float delta, uniqueScene ownScene)
{
	controller_->Update(delta);
	DrawOwnScreen(delta);

	if (controller_->Released(InputID::Down))
	{
		selectType_ = (selectType_ + 1) % static_cast<int>(PSELECT::Max);													//�I����Ԃ��������
	}

	if (controller_->Released(InputID::Up))
	{
		selectType_ = (selectType_ + (static_cast<int>(PSELECT::Max) - 1)) % static_cast<int>(PSELECT::Max);			//�I����Ԃ���グ��
	}

	if (controller_->Released(InputID::Attack))			// ����L�[�������ꂽ���̏�ԑJ��
	{
		switch (selectType_)
		{
		case static_cast<int>(PSELECT::Resume):	// ���f���̃Q�[�����ĊJ
			return std::move(beforScene_);
			break;
		case static_cast<int>(PSELECT::Retry):	// �ŏ�����v���C
			return std::make_unique<GameScene>();
			break;
		case static_cast<int>(PSELECT::SelectScene):	// �Z���N�g�V�[���Ɉڍs
			return std::make_unique<SelectScene>();
			break;
		case static_cast<int>(PSELECT::Setting):	// �ݒ�̉�ʂɈڍs
			break;
		case static_cast<int>(PSELECT::Suspension):	// �Q�[���I��
			SceneFlag_ = true;
			break;
		default:
			break;
		}
	}
	return ownScene;
}

void PauseScene::DrawOwnScreen(float delta)
{
	// �������g�̃X�N���[���ɑ΂���Draw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	beforScene_->Draw(delta);
	DrawFormatString(10, 10, 0xffffff, "PausScene");
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(140,160,920,500,0x000000,true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	SetFontSize(25);
	DrawFormatString(StringPos, OffsetY, 0xffffff, "�ĊJ");
	DrawFormatString(StringPos - 25, OffsetY + 50, 0xffffff, "���g���C");
	DrawFormatString(StringPos - 70, OffsetY + 100, 0xffffff, "�Z���N�g�֖߂�");
	DrawFormatString(StringPos, OffsetY + 150, 0xffffff, "�ݒ�");
	DrawFormatString(StringPos, OffsetY + 200, 0xffffff, "���f");

	int x = 0;
	int y = 0;
	switch (selectType_)
	{												//���݂̑I����Ԃɏ]���ď����𕪊�
	case static_cast<int>(PSELECT::Resume):				//�ĊJ��I�𒆂Ȃ�
		x = StringPos;
		y = OffsetY;
		break;
	case static_cast<int>(PSELECT::Retry):			//���g���C��I�𒆂Ȃ�
		x = StringPos -25;
		y = OffsetY + 50;
		break;
	case static_cast<int>(PSELECT::SelectScene):		//�Z���N�g��I�𒆂Ȃ�
		x = StringPos - 70;
		y = OffsetY + 100;
		break;
	case static_cast<int>(PSELECT::Setting):			//�ݒ��I�𒆂Ȃ�
		x = StringPos;
		y = OffsetY + 150;
		break;

	case static_cast<int>(PSELECT::Suspension):		// �Q�[���I��
		x = StringPos;
		y = OffsetY + 200;
		break;
	default:
		break;
	}

	DrawString(x - 40, y, "��", GetColor(255, 255, 255));

}
