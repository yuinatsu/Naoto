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
		selectType_ = (selectType_ + 1) % static_cast<int>(PSELECT::Max);													//選択状態を一つ下げる
	}

	if (controller_->Released(InputID::Up))
	{
		selectType_ = (selectType_ + (static_cast<int>(PSELECT::Max) - 1)) % static_cast<int>(PSELECT::Max);			//選択状態を一つ上げる
	}

	if (controller_->Released(InputID::Attack))			// 決定キーが押された時の状態遷移
	{
		switch (selectType_)
		{
		case static_cast<int>(PSELECT::Resume):	// 中断中のゲームを再開
			return std::move(beforScene_);
			break;
		case static_cast<int>(PSELECT::Retry):	// 最初からプレイ
			return std::make_unique<GameScene>();
			break;
		case static_cast<int>(PSELECT::SelectScene):	// セレクトシーンに移行
			return std::make_unique<SelectScene>();
			break;
		case static_cast<int>(PSELECT::Setting):	// 設定の画面に移行
			break;
		case static_cast<int>(PSELECT::Suspension):	// ゲーム終了
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
	// 自分自身のスクリーンに対してDraw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	beforScene_->Draw(delta);
	DrawFormatString(10, 10, 0xffffff, "PausScene");
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(140,160,920,500,0x000000,true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	SetFontSize(25);
	DrawFormatString(StringPos, OffsetY, 0xffffff, "再開");
	DrawFormatString(StringPos - 25, OffsetY + 50, 0xffffff, "リトライ");
	DrawFormatString(StringPos - 70, OffsetY + 100, 0xffffff, "セレクトへ戻る");
	DrawFormatString(StringPos, OffsetY + 150, 0xffffff, "設定");
	DrawFormatString(StringPos, OffsetY + 200, 0xffffff, "中断");

	int x = 0;
	int y = 0;
	switch (selectType_)
	{												//現在の選択状態に従って処理を分岐
	case static_cast<int>(PSELECT::Resume):				//再開を選択中なら
		x = StringPos;
		y = OffsetY;
		break;
	case static_cast<int>(PSELECT::Retry):			//リトライを選択中なら
		x = StringPos -25;
		y = OffsetY + 50;
		break;
	case static_cast<int>(PSELECT::SelectScene):		//セレクトを選択中なら
		x = StringPos - 70;
		y = OffsetY + 100;
		break;
	case static_cast<int>(PSELECT::Setting):			//設定を選択中なら
		x = StringPos;
		y = OffsetY + 150;
		break;

	case static_cast<int>(PSELECT::Suspension):		// ゲーム終了
		x = StringPos;
		y = OffsetY + 200;
		break;
	default:
		break;
	}

	DrawString(x - 40, y, "→", GetColor(255, 255, 255));

}
