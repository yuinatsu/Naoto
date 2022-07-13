#include "SceneMng.h"
#include <DxLib.h>
#include "../_debug/_DebugDispOut.h"
#include "../_debug/_DebugConOut.h"
#include "EditScene.h"
#include "GameScene.h"


void SceneMng::Init()
{
	SysInit();			// 重要な内容が書き込まれているのでコンストラクタ内に書いてもよい
	//uniqueBaseScene scene_ = std::make_unique<EditScene>();
	//scene_.reset(new GameScene());				// リセットシーン		スマートポインタ
	scene_ = std::make_unique<EditScene>();
}


void SceneMng::Run()
{
	Init();

	// ゲームループ
	//---------------
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//_dbgStartDraw();

		scene_ = scene_->Update(std::move(scene_));					// std::move ... （）内のものを移動
		//(*scene_).Update();				// アスタリスクよりドットの方が優先度が強いのでカッコを付ける

		Draw();
	}
}


void SceneMng::Draw()
{
	SetDrawScreen(DX_SCREEN_BACK);			// 描画する画面を裏の画面に設定
	ClearDrawScreen();						// 描画した画面をクリア

	scene_->Draw();

	_dbgAddDraw();

	ScreenFlip();
}


// システム系初期化
//-------------------
bool SceneMng::SysInit()
{
	// システム処理
	//-------------------
	SetWindowText("ロードランナー");				// ゲームウィンドウのタイトル
	SetGraphMode(scnArea_.x, scnArea_.y, 16);				// ゲームウィンドウのサイズと色モードを設定
	ChangeWindowMode(true);									// ゲームウィンドウの表示方法 (true : window   false : フルスクリーン)

	if (DxLib_Init() == -1)									// DXライブラリの初期化処理
	{
		TRACE("DxLib の初期化失敗");
		return false;										// DXライブラリの初期化失敗の為システム終了
	}

	SetDrawScreen(DX_SCREEN_BACK);							
	_dbgSetup(scnArea_.x, scnArea_.y, 255);

	return true;
}


#define VIEW_AREA_X 21
#define VIEW_AREA_Y 17


SceneMng::SceneMng() : scnArea_{ 800,600 }, worldArea_{ VIEW_AREA_X * 2,VIEW_AREA_Y }, viewArea_{ VIEW_AREA_X,VIEW_AREA_Y }, chipSize_{ 32,32 }, drawOffset_{ (scnArea_ - (viewArea_ * chipSize_)) / 2 }					// スクリーンエリアサイズ定義
{

}


SceneMng::~SceneMng()
{

}
