#include <DxLib.h>
#include "SceneCtl.h"
#include "_debug/_DebugDispOut.h"
#include "_debug/_DebugConOut.h"


// SceneCtlの生成
//-----------------
SceneCtl::SceneCtl()
{
	Init();								// Initの呼び出し
}


// SceneCtlの破棄
//-----------------
SceneCtl::~SceneCtl()
{
}


// GAME MAIN
//------------
void SceneCtl::Run(void)
{
	//Player player({ ((SCREEN_SIZE_X - 32) / 2),(SCREEN_SIZE_Y - 32) });				// playerを”インスタンスする”という
	// player.init();

	// ゲームループ
	//---------------
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		oldScnID_ = scnID_;					// 現在のIDを最初にoldに退避させておく
		if (scnID_ != nextScnID_)			// 現在のIDと次のIDが違うなら
		{
			SetupScene();					// シーンのセットアップ
		}
		nextScnID_ = scnID_;				// 次のIDを現在のIDに格納

		GetKeyData();						// キーデータ取得
		Update();							// Updateの呼び出し

		Draw();								// Drawの呼び出し
	}
	gameScene_.Relese();					// gameSceneのReleseを呼び出し
}


// SceneCtlの初期化
//-------------------
bool SceneCtl::Init(void)
{
	SysInit();										// システム系初期化
	oldScnID_ = SCN_ID::MAX;						// oldScnIDの初期ID
	scnID_ = SCN_ID::MAX;							// scnIDの初期ID
	nextScnID_ = SCN_ID::TITLE;						// nextScnIDの初期ID

	return true;
}


// システム系初期化
//-------------------
bool SceneCtl::SysInit(void)
{
	// システム処理
	//-------------------
	SetWindowText("スネークゲーム");				// ゲームウィンドウのタイトル
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);			// ゲームウィンドウのサイズと色モードを設定
	ChangeWindowMode(true);									// ゲームウィンドウの表示方法 (true : window     false : フルスクリーン)

	if (DxLib_Init() == -1)									// DXライブラリの初期化処理		Init:イニシャライズ
	{
		TRACE("DxLib の初期化失敗");
		return false;										// DXライブラリの初期化失敗の為システム終了
	}

	//srand((unsigned int)time(NULL));						// 乱数生成
	srand(256);						// 乱数生成

	//_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 255);

	return true;
}


// SceneCtlの解放
//-----------------
bool SceneCtl::Relese(void)
{
	DxLib_End();		// DXライブラリの終了処理
	return true;
}


// SceneCtlの更新
//------------------
void SceneCtl::Update(void)
{
	switch (scnID_)
	{
	case SCN_ID::TITLE:
		nextScnID_ = titleScene_.Update(keyBuf_, keyBufOld_);
		break;
	case SCN_ID::RULE:
		nextScnID_ = ruleScene_.Update(keyBuf_, keyBufOld_);
		break;
	case SCN_ID::SELECT:
		nextScnID_ = selectScene_.Update(keyBuf_, keyBufOld_);
		break;
	case SCN_ID::GAME:
		nextScnID_ = gameScene_.Update(keyBuf_, keyBufOld_);
		break;
	case SCN_ID::RESULT:
		nextScnID_ = resultScene_.Update(keyBuf_, keyBufOld_);
		break;
	default:
		TRACE("ダメ\n");
		scnID_ = SCN_ID::TITLE;
		break;
	}
}


// SceneCtlの描画
//-----------------
void SceneCtl::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);			// 描画する画面を裏の画面に設定
	ClearDrawScreen();						// 描画した画面をクリア

	switch (scnID_)
	{
	case SCN_ID::TITLE:
		titleScene_.Draw();
		break;
	case SCN_ID::RULE:
		ruleScene_.Draw();
		break;
	case SCN_ID::SELECT:
		selectScene_.Draw();
		break;
	case SCN_ID::GAME:
		gameScene_.Draw();
		break;
	case SCN_ID::RESULT:
		resultScene_.Draw();
		break;
	default:
		TRACE("ダメ\n");
		scnID_ = SCN_ID::TITLE;
		break;
	}

	ScreenFlip();
}


// キーデータ取得
//-----------------
void SceneCtl::GetKeyData(void)
{
	memcpy(keyBufOld_, keyBuf_, sizeof(keyBufOld_));			// keyBufをkeyBufOldにコピー
	GetHitKeyStateAll(keyBuf_);									// 全てのキーの状態をkeyBufに格納
}


// シーンのセットアップ
//-----------------------
void SceneCtl::SetupScene(void)
{
	ReleseScene();							// 前シーンの解放

	CHAR_ID winnerID = CHAR_ID::DRAW;		// 勝利者IDの初期ID

	switch (nextScnID_)
	{
	case SCN_ID::TITLE:
		titleScene_.Init();
		break;
	case SCN_ID::RULE:
		ruleScene_.Init();
		break;
	case SCN_ID::SELECT:
		selectScene_.Init();
		break;
	case SCN_ID::GAME:
		gameScene_.Init(selectScene_.player[0].charID_, selectScene_.player[1].charID_);						// Init(1PのキャラID, 2PのキャラID)
		break;
	case SCN_ID::RESULT:
		for (int no = 0; no < PLAYER_MAX; no++)							// プレイヤーごとの状態を確認
		{
			if (gameScene_.player[no].state_ == PL_ST::ALIVE)			// 勝利者のキャラIDを取得
			{
				winnerID = gameScene_.player[no].charID_;
			}
		}
		resultScene_.Init(winnerID);									// 勝利したキャラのIDを返す
		break;
	default:
		TRACE("ダメ\n");
		scnID_ = SCN_ID::TITLE;
		titleScene_.Init();
		break;
	}
	scnID_ = nextScnID_;
}


// 前シーンの解放
//-----------------
void SceneCtl::ReleseScene(void)
{
	switch (scnID_)
	{
	case SCN_ID::TITLE:
		titleScene_.Relese();
		break;
	case SCN_ID::RULE:
		ruleScene_.Relese();
		break;
	case SCN_ID::SELECT:
		selectScene_.Relese();
		break;
	case SCN_ID::GAME:
		gameScene_.Relese();
		break;
	case SCN_ID::RESULT:
		resultScene_.Relese();
		break;
	case SCN_ID::MAX:
		// 起動時のみ来る可能性あり
		break;
	default:
		TRACE("ダメ\n");
		break;
	}
}
