#include "SceneMng.h"
#include <DxLib.h>
#include <memory>
#include <chrono>
#include "../common/Debug.h"
#include "GameScene.h"
#include "TitleScene.h"

using namespace std;

constexpr int ScreenSizeX = 1060;
constexpr int ScreenSizeY = 660;

constexpr Math::Vector2 cameraSize{ 960,540 };

void SceneMng::Run(void)
{
	if (!InitFlag_)
	{
		// 確認のためもう一度イニシャライズする
		if (!SysInit())
		{
			return;
		}
	}

	scene_ = std::make_unique<TitleScene>();
	//scene_ = std::make_unique<GameScene>();

	chrono::system_clock::time_point nowTime, oldTime;
	nowTime = chrono::system_clock::now();
	float delta = 0.0f;
	auto flag = scene_->GetFlag();
	while (ProcessMessage() == 0 && !flag)
	{
		oldTime = nowTime;
		nowTime = chrono::system_clock::now();
		auto elTime = nowTime - oldTime;

		auto msec = chrono::duration_cast<chrono::microseconds>(elTime).count();
		delta = msec / 1000000.0f;

		scene_ = scene_->Update(delta, std::move(scene_));

		Draw(delta);
		flag = scene_->GetFlag();
	}
}

bool SceneMng::SysInit(void)
{
	DebugStart();
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return false;
	}
	DebugSetUp();
	return true;
}

void SceneMng::Update(void)
{
}

void SceneMng::Draw(float delta)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	scene_->Draw(delta);
	DebugInfoDraw(delta);
	ScreenFlip();
}

SceneMng::SceneMng()
{
	InitFlag_ = SysInit();
}

SceneMng::~SceneMng()
{
}
