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
			selectType_ = (selectType_ + 1) % static_cast<int>(SELECT_TYPE::Max);//選択状態を一つ下げる
		}			
	}

	if (controller_->Released(InputID::Left))
	{
		// PlaySoundMem(se1, DX_PLAYTYPE_BACK);
		SoundProcess::DoSound(SoundProcess::ESOUNDNAME_SE::testse);
		if (selectType_ > static_cast<int>(SELECT_TYPE::StageOne))
		{
			selectType_ = (selectType_ + (static_cast<int>(SELECT_TYPE::Max) - 1)) % static_cast<int>(SELECT_TYPE::Max);			//選択状態を一つ上げる
		}
	}

	if (controller_->Released(InputID::Attack))			// 決定キーが押された時の状態遷移
	{
		SoundProcess::DoSound(SoundProcess::ESOUNDNAME_SE::testse);

		switch (selectType_)
		{
		case static_cast<int>(SELECT_TYPE::StageOne):	// selectTypeがStageOneだった場合、ゲームシーンに移行する
			mapNum_ = selectType_ + 1;
			return std::make_unique<CircleScene>(
				2.0,
				std::move(ownScene),
				std::make_unique<GameScene>()
				);
			break;
		case static_cast<int>(SELECT_TYPE::StageTwo):	// selectTypeがStageOneだった場合、ゲームシーンに移行する
			mapNum_ = selectType_ + 1;
			return std::make_unique<CircleScene>(
				2.0,
				std::move(ownScene),
				std::make_unique<GameScene>()
				);
			break;
		case static_cast<int>(SELECT_TYPE::StageThree):	// selectTypeがStageOneだった場合、ゲームシーンに移行する
			mapNum_ = selectType_ + 1;
			return std::make_unique<CircleScene>(
				2.0,
				std::move(ownScene),
				std::make_unique<GameScene>()
				);
			break;
		case static_cast<int>(SELECT_TYPE::StageFour):	// selectTypeがStageOneだった場合、ゲームシーンに移行する
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
	// 自分自身のスクリーンに対してDraw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawFormatString(10, 10, 0xffffff, "SelectScene");
	int x = 0;
	int y = 0;
	switch (selectType_)
	{												//現在の選択状態に従って処理を分岐
	case static_cast<int>(SELECT_TYPE::StageOne):	//ステージ1を選択中なら
		minRate_stage_two = 0;

		x = StringPos;								//ステージ1の座標を格納
		y = OffsetY;
		if (minRate_ <= maxRate_)
		{
			minRate_ += speed;
		}
		DrawRotaGraph(mapPicPosX, mapPicPosY, minRate_, 0, gameMap_, true);

		selecterPicFlag_ = true;
		selecterPicLFlag_ = false;
		DrawFormatString((ScreenSizeX / 2 - selecterLPos_) +250 ,(ScreenSizeY / 2 + selecterLPos_) - 130, 0xffffff, "ステージ1");
		break;
	case static_cast<int>(SELECT_TYPE::StageTwo):	//ステージ2を選択中なら
		minRate_ = 0;
		minRate_stage_three = 0;
		x = StringPos;								//ステージ2の座標を格納
		y = OffsetY;
		if (minRate_stage_two <= maxRate_)
		{
			minRate_stage_two += speed;
		}
		DrawRotaGraph(mapPicPosX, mapPicPosY, minRate_stage_two, 0, gameMap_, true);

		selecterPicFlag_ = true;
		selecterPicLFlag_ = true;
		DrawFormatString((ScreenSizeX / 2 - selecterLPos_) + 250, (ScreenSizeY / 2 + selecterLPos_) - 130, 0xffffff, "ステージ2");
		break;
	case static_cast<int>(SELECT_TYPE::StageThree):	//ステージ2を選択中なら
		minRate_stage_two = 0;
		minRate_stage_four = 0;
		x = StringPos;							//ステージ2の座標を格納
		y = OffsetY;
		if (minRate_stage_three <= maxRate_)
		{
			minRate_stage_three += speed;
		}
		DrawRotaGraph(mapPicPosX, mapPicPosY, minRate_stage_three, 0, gameMap_, true);

		selecterPicFlag_ = true;
		selecterPicLFlag_ = true;
		DrawFormatString((ScreenSizeX / 2 - selecterLPos_) + 250, (ScreenSizeY / 2 + selecterLPos_) - 130, 0xffffff, "ステージ3");
		break;
	case static_cast<int>(SELECT_TYPE::StageFour):	//ステージ2を選択中なら
		minRate_stage_three = 0;
		x = StringPos;								//ステージ2の座標を格納
		y = OffsetY;

		if (minRate_stage_four <= maxRate_)
		{
			minRate_stage_four += speed;
		}
		DrawRotaGraph(mapPicPosX, mapPicPosY, minRate_stage_four, 0, gameMap_, true);

		selecterPicFlag_ = false;
		selecterPicLFlag_ = true;
		DrawFormatString((ScreenSizeX / 2 - selecterLPos_) + 250, (ScreenSizeY / 2 + selecterLPos_) - 130, 0xffffff, "ステージ4");
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


