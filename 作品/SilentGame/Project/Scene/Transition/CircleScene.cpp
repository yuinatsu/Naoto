#include <DxLib.h>
#include "CircleScene.h"

constexpr int ScreenSizeX = 1060;
constexpr int ScreenSizeY = 660;

CircleScene::CircleScene(double limitTime, uniqueScene beforScene, uniqueScene afterScene):
    TransitionScene(std::move(beforScene), std::move(afterScene))
{
	limitTime_ = limitTime;

	DrawOwnScreen(0.0);
}

CircleScene::~CircleScene()
{

}

bool CircleScene::UpdataTransition(double delta)
{
	count += delta;
	// limitTime秒経ったら次のシーンへ以降
	// トランジションが終わっていればtrue
	if (count > limitTime_)
	{
		return true;
	}
	// 終わっていなければfalse
	return false;
}

void CircleScene::DrawOwnScreen(float delta)
{
	// 自分自身のスクリーンに対してDraw
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	auto alpha = static_cast<int>(255 * count / limitTime_);
	// 透明にする計算
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - alpha);
	beforScene_->Draw(delta);
	// 色をつける
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	afterScene_->Draw(delta);
	// ずっと有効になってしまうので無効にする命令
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);

	int i = static_cast<int>(550 * count / limitTime_);

	DrawReversalCircle(ScreenSizeX / 2, ScreenSizeY / 2, i, 0xffffff);
}

int CircleScene::DrawReversalCircle(int x, int y, int r, int Color)
{
	// 円反転描画領域の外側を描画
	DrawBox(0, 0, 1060, y - r, Color, true);
	DrawBox(0, y - r, x - r, 660, Color, true);
	DrawBox(x - r, y + r + 1, 1060, 660, Color, true);
	DrawBox(x + r, y - r, 1060, y + r + 1, Color, true);
	return 0;
}

