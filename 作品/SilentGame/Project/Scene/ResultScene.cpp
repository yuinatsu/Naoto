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
		// 仮で選択しているものを変更する
		if (controller_->Released(InputID::Up)) // 上キーが押されていたら
		{
			selectType_ = (selectType_ + (static_cast<int>(TSELECT::Max) - 1)) % static_cast<int>(TSELECT::Max);
		}
		if (controller_->Released(InputID::Down)) // 下キーが押されていたら
		{
			selectType_ = (selectType_ + 1) % (static_cast<int>(TSELECT::Max));;
		}
		// シーン移行する
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
		DrawFormatString(0, 40, 0xffffff, "倒した敵の数=%d体", Ndefeats_);
	}
	if (emTime_ >= 2.0f)
	{
		DrawFormatString(0, 70, 0xffffff, "経過時間=%.2f秒", elTime_);
	}
	switch (selectType_)
	{												//現在の選択状態に従って処理を分岐
	case static_cast<int>(RSELECT::Retry):				//スタートを選択中なら
		x = StringPos - 20;
		y = OffsetY;
		break;
	case static_cast<int>(RSELECT::Select):			//終了を選択中なら
		x = StringPos - 40;
		y = OffsetY + 50;
		break;
	case static_cast<int>(RSELECT::Title):		//設定を選択中なら
		x = StringPos - 30;
		y = OffsetY + 100;
		break;
	default:
		break;
	}
	if (emTime_ >= 3.0f)
	{
		DrawString(StringPos - 20, OffsetY, "リトライ", 0xffffff);
		DrawString(StringPos - 40, OffsetY + 50, "シーン選択へ", 0xffffff);
		DrawString(StringPos - 30, OffsetY + 100, "タイトルへ", 0xffffff);
		DrawString(x - 40, y, "→", GetColor(255, 255, 255));
	}

	//自分自身のスクリーンに対してDraw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(50, 60, viewID_, true);


	DrawFormatString(10, 10, 0xffffff, "ResultScene");
}
