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

	// 仮で選択しているものを変更する
	if (controller_->Released(InputID::Down)) // 上キーが押されていたら
	{
		selectType_ = (selectType_ + (static_cast<int>(TSELECT::Max) -1)) % static_cast<int>(TSELECT::Max);			//選択状態を一つ上げる
	}
	if (controller_->Released(InputID::Up)) // 下キーが押されていたら
	{
		selectType_ = (selectType_ + 1) % (static_cast<int>(TSELECT::Max));													//選択状態を一つ下げる
	}

	// シーン移行する
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
	// 自分自身のスクリーンに対してDraw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	SetFontSize(60);
	DrawFormatString(StringPos - 120, 150, 0xffffff, "SilentGame");

	SetFontSize(25);
	DrawFormatString(StringPos-40, OffsetY, 0xffffff, "ゲーム開始");
	DrawFormatString(StringPos-40, OffsetY +50, 0xffffff, "ゲーム終了");
	int x = 0;
	int y = 0;
	switch (selectType_)
	{												//現在の選択状態に従って処理を分岐
	case static_cast<int>(TSELECT::Start):				//スタートを選択中なら
		x = StringPos -40;
		y = OffsetY;
		break;
	case static_cast<int>(TSELECT::Suspension):			//終了を選択中なら
		x = StringPos - 40;
		y = OffsetY + 50;
		break;
	//case static_cast<int>(SELECT::Setting):		//設定を選択中なら
	//	x = StringPos - 70;
	//	y = OffsetY + 100;
	//	break;
	default:
		break;
	}

	DrawString(x - 40, y, "→", GetColor(255, 255, 255));
}
