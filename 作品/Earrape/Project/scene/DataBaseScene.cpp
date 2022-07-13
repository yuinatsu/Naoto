#include <DxLib.h>
#include "DataBaseScene.h"
#include "../FilePass.h"
#include "../input/Mouse.h"
#include "SceneCtl.h"
#include "../FileSize.h"
#include "../_debug/_DebugConOut.h"

DataBaseScene::DataBaseScene()
{
}

DataBaseScene::~DataBaseScene()
{
}

SCN_ID DataBaseScene::Update(char* keyData, char* keyDataOld)
{
	lpMouse.Update();
	const auto inputData = lpMouse.GetData(InputType::NOW);
	const auto inputDataOld = lpMouse.GetData(InputType::OLD);
	pos_.x = inputData.at("X座標");
	pos_.y = inputData.at("Y座標");

	sctFlag1_ = false;
	sctFlag2_ = false;

	//TRACE("x:%d  y:%d\n", pos_.x, pos_.y);//マウス座標デバッグ表示

	if (inputData.count("X座標") && inputData.count("Y座標"))
	{
		//項目１：WEAPON
		auto sctPosA = (lpSceneCtl.scnArea_.x - lpSize.titleSect1_.x) / 2;
		auto sctPosB = (lpSceneCtl.scnArea_.y + (lpSize.titleSect1_.y * 1)) / 2;
		if ((pos_.x >= sctPosA) && (pos_.y >= sctPosB) &&
			(pos_.x <= sctPosA + lpSize.titleSect1_.x) && (pos_.y <= sctPosB + lpSize.titleSect1_.y))
		{
			sctFlag1_ = true;
			if (lpMouse.GetPresCnt(Mouse::LMB) == 1)
			{
				TRACE("DataBaseSceneからWeaponSceneに移行\n");
				ChangeVolumeSoundMem(255 * lpSceneCtl.CVS / 100, atfSE_);//音量設定
				PlaySoundMem(atfSE_, DX_PLAYTYPE_NORMAL, true);
				return SCN_ID::WEAPON;
			}
		}
		//項目２：PERFORM
		auto sctPosC = (lpSceneCtl.scnArea_.x - lpSize.titleSect2_.x) / 2;
		auto sctPosD = (lpSceneCtl.scnArea_.y + (lpSize.titleSect2_.y * 5)) / 2;
		if ((pos_.x >= sctPosC) && (pos_.y >= sctPosD) &&
			(pos_.x <= sctPosC + lpSize.titleSect2_.x) && (pos_.y <= sctPosD + lpSize.titleSect2_.y))
		{
			sctFlag2_ = true;
			if (lpMouse.GetPresCnt(Mouse::LMB) == 1)
			{
				TRACE("DataBaseSceneからPerformSceneに移行\n");
				ChangeVolumeSoundMem(255 * lpSceneCtl.CVS / 100, atfSE_);//音量設定
				PlaySoundMem(atfSE_, DX_PLAYTYPE_NORMAL, true);
				return SCN_ID::PERFORM;
			}
		}
	}
	if (lpMouse.GetPresCnt(Mouse::RMB) == 1)
	{
		// 右クリックされた瞬間
		PlaySoundFile(SH_buttonSE, DX_PLAYTYPE_BACK);
		return SCN_ID::TITLE;
	}
	//if (keyData[KEY_INPUT_SPACE] && !keyDataOld[KEY_INPUT_SPACE])
	//{
	//	return SCN_ID::TITLE;
	//}
	blinkCnt_++;
	//if (keyData[KEY_INPUT_SPACE] && !keyDataOld[KEY_INPUT_SPACE])
	//{
	//	PlaySoundMem(atfSE_, DX_PLAYTYPE_NORMAL, true);
	//	return SCN_ID::TITLE;
	//}
	return SCN_ID::DATABASE;
}

void DataBaseScene::Draw(void)
{
	DrawGraph(0, 0, dbbg_, true);

	DrawGraph(0, 0, dbLogoBW_, true);
	if ((blinkCnt_ / 20) % 2)
	{
		DrawGraph(0, 0, dbLogoBO_, true);
	}

	if (!sctFlag1_)
	{
		DrawGraph((lpSceneCtl.scnArea_.x - lpSize.titleSect1_.x) / 2, (lpSceneCtl.scnArea_.y + (lpSize.titleSect1_.y * 1)) / 2, section1_BW_, true);
	}
	if (!sctFlag2_)
	{
		DrawGraph((lpSceneCtl.scnArea_.x - lpSize.titleSect2_.x) / 2, (lpSceneCtl.scnArea_.y + (lpSize.titleSect2_.y * 5)) / 2, section2_BW_, true);
	}

	if (sctFlag1_)
	{
		DrawGraph((lpSceneCtl.scnArea_.x - lpSize.titleSect1_.x) / 2, (lpSceneCtl.scnArea_.y + (lpSize.titleSect1_.y * 1)) / 2, section1_BO_, true);
	}
	if (sctFlag2_)
	{
		DrawGraph((lpSceneCtl.scnArea_.x - lpSize.titleSect2_.x) / 2, (lpSceneCtl.scnArea_.y + (lpSize.titleSect2_.y * 5)) / 2, section2_BO_, true);
	}
}

bool DataBaseScene::Init(void)
{
	blinkCnt_ = 0;

	dbbg_ = LoadGraph(GH_BG_DATABESE);
	dbLogoBO_ = LoadGraph(GH_LOGO_DATABASE_BO);
	dbLogoBW_ = LoadGraph(GH_LOGO_DATABASE_BW);
	section1_BO_ = LoadGraph(GH_LOGO_TITLE_DATABASE_1_BO);
	section1_BW_ = LoadGraph(GH_LOGO_TITLE_DATABASE_1_BW);
	section2_BO_ = LoadGraph(GH_LOGO_TITLE_DATABASE_2_BO);
	section2_BW_ = LoadGraph(GH_LOGO_TITLE_DATABASE_2_BW);
	atfSE_ = LoadSoundMem(SH_ATF);
	PlaySoundFile(SH_buttonSE, DX_PLAYTYPE_BACK);
	return true;
}

bool DataBaseScene::Release(void)
{
	DeleteGraph(dbbg_);
	DeleteGraph(dbLogoBO_);
	DeleteGraph(dbLogoBW_);
	DeleteGraph(atfSE_);
	return true;
}
