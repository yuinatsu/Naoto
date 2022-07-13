#include <DxLib.h>
#include "TitleScene.h"
#include "SelectScene.h"
#include "Transition/FadeTrans.h"

TitleScene::TitleScene()
{
	Init();
	DrawOwnScreen(0.0);
}

TitleScene::~TitleScene()
{
}

bool TitleScene::Init(void)
{
	return true;
}

uniqueScene TitleScene::Update(float delta, uniqueScene ownScene)
{

	controller_->Update(delta);

	// ���őI�����Ă�����̂�ύX����
	if (controller_->Released(InputID::Down)) // ��L�[��������Ă�����
	{
		selectType_ = (selectType_ + (static_cast<int>(TSELECT::Max) -1)) % static_cast<int>(TSELECT::Max);			//�I����Ԃ���グ��
	}
	if (controller_->Released(InputID::Up)) // ���L�[��������Ă�����
	{
		selectType_ = (selectType_ + 1) % (static_cast<int>(TSELECT::Max));													//�I����Ԃ��������
	}

	// �V�[���ڍs����
	if (controller_->Released(InputID::Attack))
	{
		switch (selectType_)
		{
		case static_cast<int>(TSELECT::Start):
			return std::make_unique<FadeTrans>(
				1.0f,
				std::move(ownScene),
				std::make_unique<SelectScene>()
				);
			break;
		case static_cast<int>(TSELECT::Suspension):
			SceneFlag_ = true;
			break;
		case  static_cast<int>(TSELECT::Setting):
			return std::make_unique<TitleScene>();
			break;
		default:
			break;
		}
	}

	DrawOwnScreen(delta);
	return ownScene;
}

void TitleScene::DrawOwnScreen(float delta)
{
	// �������g�̃X�N���[���ɑ΂���Draw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	SetFontSize(60);
	DrawFormatString(StringPos - 120, 150, 0xffffff, "SilentGame");

	SetFontSize(25);
	DrawFormatString(StringPos-40, OffsetY, 0xffffff, "�Q�[���J�n");
	DrawFormatString(StringPos-40, OffsetY +50, 0xffffff, "�Q�[���I��");
	int x = 0;
	int y = 0;
	switch (selectType_)
	{												//���݂̑I����Ԃɏ]���ď����𕪊�
	case static_cast<int>(TSELECT::Start):				//�X�^�[�g��I�𒆂Ȃ�
		x = StringPos -40;
		y = OffsetY;
		break;
	case static_cast<int>(TSELECT::Suspension):			//�I����I�𒆂Ȃ�
		x = StringPos - 40;
		y = OffsetY + 50;
		break;
	//case static_cast<int>(SELECT::Setting):		//�ݒ��I�𒆂Ȃ�
	//	x = StringPos - 70;
	//	y = OffsetY + 100;
	//	break;
	default:
		break;
	}

	DrawString(x - 40, y, "��", GetColor(255, 255, 255));
}
