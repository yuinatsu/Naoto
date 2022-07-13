#include <DxLib.h>
#include "ResultScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "TitleScene.h"

ResultScene::ResultScene()
{
	Init();
	DrawOwnScreen(0.0);
}

ResultScene::ResultScene(int Ndefeats, float eltime)
{
	emTime_ = 0.0f;
	scSize_ = Math::Vector2I(960, 540);
	viewID_ = MakeScreen(scSize_.x, scSize_.y, 255);
	Ndefeats_ = Ndefeats;
	elTime_ = eltime;
	SceneFlag_ = false;
	Init();
}

ResultScene::~ResultScene()
{
}

bool ResultScene::Init(void)
{
    return true;
}

uniqueScene ResultScene::Update(float delta, uniqueScene ownScene)
{
	if (emTime_ >= 3)
	{
		// ���őI�����Ă�����̂�ύX����
		if (controller_->Released(InputID::Up)) // ��L�[��������Ă�����
		{
			selectType_ = (selectType_ + (static_cast<int>(TSELECT::Max) - 1)) % static_cast<int>(TSELECT::Max);
		}
		if (controller_->Released(InputID::Down)) // ���L�[��������Ă�����
		{
			selectType_ = (selectType_ + 1) % (static_cast<int>(TSELECT::Max));;
		}
		// �V�[���ڍs����
		if (controller_->Released(InputID::Attack))
		{
			switch (selectType_)
			{
			case static_cast<int>(RSELECT::Retry):
				return std::make_unique<GameScene>();
				break;
			case static_cast<int>(RSELECT::Select):
				return std::make_unique<SelectScene>();
				break;
			case static_cast<int>(RSELECT::Title):
				return std::make_unique<TitleScene>();
				break;
			default:
				break;
			}
		}
	}
	emTime_ += delta;
	controller_->Update(delta);

	DrawOwnScreen(delta);

	return ownScene;
}

void ResultScene::DrawOwnScreen(float delta)
{
	int x = 0;
	int y = 0;
	SetDrawScreen(viewID_);
	ClsDrawScreen();
	SetDrawBright(255, 255, 255);
	SetFontSize(25);
	if (emTime_ >= 1.0f)
	{
		DrawFormatString(0, 40, 0xffffff, "�|�����G�̐�=%d��", Ndefeats_);
	}
	if (emTime_ >= 2.0f)
	{
		DrawFormatString(0, 70, 0xffffff, "�o�ߎ���=%.2f�b", elTime_);
	}
	switch (selectType_)
	{												//���݂̑I����Ԃɏ]���ď����𕪊�
	case static_cast<int>(RSELECT::Retry):				//�X�^�[�g��I�𒆂Ȃ�
		x = StringPos - 20;
		y = OffsetY;
		break;
	case static_cast<int>(RSELECT::Select):			//�I����I�𒆂Ȃ�
		x = StringPos - 40;
		y = OffsetY + 50;
		break;
	case static_cast<int>(RSELECT::Title):		//�ݒ��I�𒆂Ȃ�
		x = StringPos - 30;
		y = OffsetY + 100;
		break;
	default:
		break;
	}
	if (emTime_ >= 3.0f)
	{
		DrawString(StringPos - 20, OffsetY, "���g���C", 0xffffff);
		DrawString(StringPos - 40, OffsetY + 50, "�V�[���I����", 0xffffff);
		DrawString(StringPos - 30, OffsetY + 100, "�^�C�g����", 0xffffff);
		DrawString(x - 40, y, "��", GetColor(255, 255, 255));
	}

	//�������g�̃X�N���[���ɑ΂���Draw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(50, 60, viewID_, true);


	DrawFormatString(10, 10, 0xffffff, "ResultScene");
}
