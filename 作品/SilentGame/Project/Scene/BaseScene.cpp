#include <DxLib.h>
#include <string>
#include "BaseScene.h"
#include "../Input/Keyboard.h"
#include "../Input/Pad.h"

BaseScene::BaseScene()
{
	SetDrawScreen(DX_SCREEN_BACK);		// 明示的にバックバッファを指定
	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);	// 描画先のサイズを取得する(バッファ）
	screenID_ = MakeScreen(screenSize_.x, screenSize_.y, true);		// スクリーンのサイズ
	// コントローラー情報
	if (GetJoypadNum())
	{
		controller_ = std::make_unique<Pad>();
	}
	else
	{
		controller_ = std::make_unique<Keyboard>();
	}
	mapNum_ = 1;
}

BaseScene::~BaseScene()
{

}

void BaseScene::Draw(float delta)
{
	// screenIDに対して描画
	DrawGraph(0, 0, screenID_, true);
}
