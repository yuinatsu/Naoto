#include <DxLib.h>
#include "SelectScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "PauseScene.h"
#include "Transition/CircleScene.h"
#include"../common/SoundPross.h"
SelectScene::SelectScene()
{
	Init(); 
	DrawOwnScreen(0.0);
}

SelectScene::~SelectScene()
{
	SoundProcess::Release();
}

bool SelectScene::Init(void)
{
	SceneFlag_ = false;
	selectType_ = static_cast<int>(SELECT_TYPE::StageOne);
	selecterPic_ = LoadGraph("Resource/Image/SelectScene/selecter.png");
	selecterLPic_ = LoadGraph("Resource/Image/SelectScene/selecter_L.png");
	gameMap_ = LoadGraph("Resource/Image/SelectScene/gameMap.png");


	SoundProcess::Init();
	se1 = LoadSoundMem("Resource/Sound/enter.mp3");
	SoundProcess::Load(se1, SoundProcess::ESOUNDNAME_SE::testse);

	return true;
}

uniqueScene SelectScene::Update(float delta, uniqueScene ownScene)
{
	DrawOwnScreen(delta);
	controller_->Update(delta);

	if (controller_->Released(InputID::Right))
	{
		// PlaySoundMem(se1, DX_PLAYTYPE_BACK);
		SoundProcess::DoSound(SoundProcess::ESOUNDNAME_SE::testse);
		if (selectType_ < static_cast<int>(SELECT_TYPE::StageFour))
		{
			selectType_ = (selectType_ + 1) % static_cast<int>(SELECT_TYPE::Max);//�I����Ԃ��������
		}			
	}

	if (controller_->Released(InputID::Left))
	{
		// PlaySoundMem(se1, DX_PLAYTYPE_BACK);
		SoundProcess::DoSound(SoundProcess::ESOUNDNAME_SE::testse);
		if (selectType_ > static_cast<int>(SELECT_TYPE::StageOne))
		{
			selectType_ = (selectType_ + (static_cast<int>(SELECT_TYPE::Max) - 1)) % static_cast<int>(SELECT_TYPE::Max);			//�I����Ԃ���グ��
		}
	}

	if (controller_->Released(InputID::Attack))			// ����L�[�������ꂽ���̏�ԑJ��
	{
		SoundProcess::DoSound(SoundProcess::ESOUNDNAME_SE::testse);

		switch (selectType_)
		{
		case static_cast<int>(SELECT_TYPE::StageOne):	// selectType��StageOne�������ꍇ�A�Q�[���V�[���Ɉڍs����
			mapNum_ = selectType_ + 1;
			return std::make_unique<CircleScene>(
				2.0,
				std::move(ownScene),
				std::make_unique<GameScene>()
				);
			break;
		case static_cast<int>(SELECT_TYPE::StageTwo):	// selectType��StageOne�������ꍇ�A�Q�[���V�[���Ɉڍs����
			mapNum_ = selectType_ + 1;
			return std::make_unique<CircleScene>(
				2.0,
				std::move(ownScene),
				std::make_unique<GameScene>()
				);
			break;
		case static_cast<int>(SELECT_TYPE::StageThree):	// selectType��StageOne�������ꍇ�A�Q�[���V�[���Ɉڍs����
			mapNum_ = selectType_ + 1;
			return std::make_unique<CircleScene>(
				2.0,
				std::move(ownScene),
				std::make_unique<GameScene>()
				);
			break;
		case static_cast<int>(SELECT_TYPE::StageFour):	// selectType��StageOne�������ꍇ�A�Q�[���V�[���Ɉڍs����
			mapNum_ = selectType_ + 1;
			return std::make_unique<CircleScene>(
				2.0,
				std::move(ownScene),
				std::make_unique<GameScene>()
				);
			break;
		default:
			break;
		}
	}

	//if (controller_->Released(InputID::btn1))
	//{
	//	return std::make_unique<GameScene>();
	//}

	return ownScene;
}

void SelectScene::DrawOwnScreen(float delta)
{
	// �������g�̃X�N���[���ɑ΂���Draw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawFormatString(10, 10, 0xffffff, "SelectScene");
	int x = 0;
	int y = 0;
	switch (selectType_)
	{												//���݂̑I����Ԃɏ]���ď����𕪊�
	case static_cast<int>(SELECT_TYPE::StageOne):	//�X�e�[�W1��I�𒆂Ȃ�
		minRate_stage_two = 0;

		x = StringPos;								//�X�e�[�W1�̍��W���i�[
		y = OffsetY;
		if (minRate_ <= maxRate_)
		{
			minRate_ += speed;
		}
		DrawRotaGraph(mapPicPosX, mapPicPosY, minRate_, 0, gameMap_, true);

		selecterPicFlag_ = true;
		selecterPicLFlag_ = false;
		DrawFormatString((ScreenSizeX / 2 - selecterLPos_) +250 ,(ScreenSizeY / 2 + selecterLPos_) - 130, 0xffffff, "�X�e�[�W1");
		break;
	case static_cast<int>(SELECT_TYPE::StageTwo):	//�X�e�[�W2��I�𒆂Ȃ�
		minRate_ = 0;
		minRate_stage_three = 0;
		x = StringPos;								//�X�e�[�W2�̍��W���i�[
		y = OffsetY;
		if (minRate_stage_two <= maxRate_)
		{
			minRate_stage_two += speed;
		}
		DrawRotaGraph(mapPicPosX, mapPicPosY, minRate_stage_two, 0, gameMap_, true);

		selecterPicFlag_ = true;
		selecterPicLFlag_ = true;
		DrawFormatString((ScreenSizeX / 2 - selecterLPos_) + 250, (ScreenSizeY / 2 + selecterLPos_) - 130, 0xffffff, "�X�e�[�W2");
		break;
	case static_cast<int>(SELECT_TYPE::StageThree):	//�X�e�[�W2��I�𒆂Ȃ�
		minRate_stage_two = 0;
		minRate_stage_four = 0;
		x = StringPos;							//�X�e�[�W2�̍��W���i�[
		y = OffsetY;
		if (minRate_stage_three <= maxRate_)
		{
			minRate_stage_three += speed;
		}
		DrawRotaGraph(mapPicPosX, mapPicPosY, minRate_stage_three, 0, gameMap_, true);

		selecterPicFlag_ = true;
		selecterPicLFlag_ = true;
		DrawFormatString((ScreenSizeX / 2 - selecterLPos_) + 250, (ScreenSizeY / 2 + selecterLPos_) - 130, 0xffffff, "�X�e�[�W3");
		break;
	case static_cast<int>(SELECT_TYPE::StageFour):	//�X�e�[�W2��I�𒆂Ȃ�
		minRate_stage_three = 0;
		x = StringPos;								//�X�e�[�W2�̍��W���i�[
		y = OffsetY;

		if (minRate_stage_four <= maxRate_)
		{
			minRate_stage_four += speed;
		}
		DrawRotaGraph(mapPicPosX, mapPicPosY, minRate_stage_four, 0, gameMap_, true);

		selecterPicFlag_ = false;
		selecterPicLFlag_ = true;
		DrawFormatString((ScreenSizeX / 2 - selecterLPos_) + 250, (ScreenSizeY / 2 + selecterLPos_) - 130, 0xffffff, "�X�e�[�W4");
		break;

	default:
		break;
	}

	if (selecterPicLFlag_)
	{
		DrawRotaGraph((ScreenSizeX / 2) + (x - (ScreenSizeX / 2 + selecterLPos_)), (ScreenSizeY / 2) + (y - (ScreenSizeY / 2 - 10)), 0.1, 0, selecterLPic_, true);
	}

	if (selecterPicFlag_)
	{
		DrawRotaGraph((ScreenSizeX / 2) - (x - (ScreenSizeX / 2 + selecterLPos_)), (ScreenSizeY / 2) + (y - (ScreenSizeY / 2 - 10)), 0.1, 0, selecterPic_, true);
	}

}


