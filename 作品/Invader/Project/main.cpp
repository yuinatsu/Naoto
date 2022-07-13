//---------------------------------
// ゲーム制作：基本ソース
// 氏名　　　：2016010 梶原尚人
//---------------------------------

#include "time.h"
#include "DxLib.h"			// DXライブラリの使用
#include "main.h"
#include "_debug/_DebugDispOut.h"
#include "_debug/_DebugConOut.h"

// 変数定義
//-----------------
int y, x, n;

int blinkCnt;										// 点滅表示カウンタ

// シーン関係
//-----------------
SCENE_ID scnID;										// 現在のシーン

// キーバッファ
//-----------------
char keyBuf[256];
char keyBufOld[256];

// タイトル関係
//-----------------
int titleImage;										// グラフィックハンドル
int titlePosX;										// X座標
int titlePosY;										// Y座標

// ゲームオーバー関係
//-----------------
int gameOverImage;									// グラフィックハンドル
int gameOverPosX;									// X座標
int gameOverPosY;									// Y座標
int gameOverCnt;									// 矢印Y座標

// スコア関係
//-----------------
int scrData;										// 現在のスコア						昔はスコアは500としたら、下2桁の00は画面表示のみにして、メモリには5のみを格納することでメモリの節約を行った
int hiScrData;										// ハイスコア

// 自機関係
//-----------------
int playerImage[DIR_MAX][ANIM_MAX];					// グラフィックハンドル
int playerPosX;										// X座標
int playerPosY;										// Y座標
int playerSpeed;									// 移動量
bool playerAlive;									// 生存フラグ
int playerAnimCnt;									// アニメーションフラグ
int pAnimCnt;										// アニメーションカウンタ
int playerLife;										// 自機の残機数						intでもcharでもOK

// 敵関係
//-----------------
int enemyImage[ENEMY_TYPE_MAX][DIR_MAX][ANIM_MAX];	// グラフィックハンドル
int enemyPosX[ENEMY_COUNT_Y][ENEMY_COUNT_X];		// X座標
int enemyPosY[ENEMY_COUNT_Y][ENEMY_COUNT_X];		// Y座標
DIR_ID enemyDir[ENEMY_COUNT_Y][ENEMY_COUNT_X];		// 敵の発射方向
int enemySpeed;										// 移動量
bool enemyAlive[ENEMY_COUNT_Y][ENEMY_COUNT_X];		// 生存フラグ
int enemyMoveCnt;									// 敵の移動カウンタ
int enemyAnimCnt;									// アニメーションフラグ
int eAnimCnt;										// アニメーションカウンタ
MOVE_LR enemyMoveFlagX;								// 敵の左右移動管理用
MOVE_MODE enemyMoveMode;							// 敵の左右移動か下移動の管理用
DIR_ID dir;											// 敵方向転換アニメーション

// 自機の弾関係
//-----------------
int pShotImage;										// グラフィックハンドル
int pShotPosX;										// X座標
int pShotPosY;										// Y座標
int pShotSpeed;										// 移動量
bool pShotAlive;									// 発射フラグ

// 敵の弾関係
//-----------------
int eShotImage;										// グラフィックハンドル
int eShotPosX[ENEMY_COUNT_X];						// X座標
int eShotPosY[ENEMY_COUNT_X];						// Y座標
int eShotSpeed;										// 移動量
bool eShotAlive[ENEMY_COUNT_X];						// 発射フラグ

// WinMain関数
//-----------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!SysInit())
	{
		TRACE("初期化失敗");
		return -1;
	}


	// ゲームループ
	//---------------------
	while (ProcessMessage() == 0 && keyBuf[KEY_INPUT_ESCAPE] == 0)
	{
		//for (n = 0; 0 < 256; n++)					// memcpyの処理と同義
		//{
		//	keyBufOld[n] = keyBuf[n];
		//}

		memcpy(keyBufOld, keyBuf, sizeof(keyBufOld));			// sizeof(keyBufOld) / sizeof(keyBufOld[0])
		GetHitKeyStateAll(keyBuf);

		_dbgStartDraw();


		// シーン設定処理
		//---------------------
		switch (scnID)							// 正常値はcaseですべて書く.....異常値と正常値を混在させてしまうから  >>   switchはいずれ撲滅される(行を無駄に使うから)
		{
		case SCENE_ID_TITLE:
			TitleScene();
			break;

		case SCENE_ID_GAME:
			GameScene();
			break;

		case SCENE_ID_GAMEOVER:
			GameOverScene();
			break;

		case SCENE_ID_RULE:
			RuleScene();
			break;

		default:
			break;
		}
	}
	
	// システム終了処理
	//--------------------
	DxLib::DxLib_End();		// DXライブラリの終了処理
	return 0;		// ゲームの終了
}







// タイトル画面
//---------------------
void TitleScene(void)
{
	TitleDraw();

	if (keyBuf[KEY_INPUT_Z] && !keyBufOld[KEY_INPUT_Z])
	{
		GameInit();
		scnID = SCENE_ID_GAME;					// キーを押したらゲームシーンに移動
	}
}


// タイトル描画処理
//---------------------
void TitleDraw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();


	DrawBox(GAME_SCREEN_X, GAME_SCREEN_Y, GAME_SCREEN_X + GAME_SCREEN_SIZE_X, GAME_SCREEN_Y + GAME_SCREEN_SIZE_Y, GetColor(30, 30, 30), true);

	DrawGraph(titlePosX, titlePosY, titleImage, true);					// タイトルロゴ描画

	if ((blinkCnt / 30) % 2)
	{
		int ScrWidth = GetDrawStringWidth("PHSH Z KEY", strlen("PHSH Z KEY"));
		DrawString(GAME_SCREEN_X + (GAME_SCREEN_SIZE_X - ScrWidth) / 2, GAME_SCREEN_Y + (GAME_SCREEN_SIZE_Y * 2 / 3), "PUSH Z KEY", 0x00ff00);				// "PHSH Z KEY"の文字列を描画
	}

	ScrDraw();

	ScreenFlip();

	blinkCnt++;
}


// ルール説明用画面
//---------------------
void RuleScene(void)
{
	RuleDraw();

	if (keyBuf[KEY_INPUT_Z] && !keyBufOld[KEY_INPUT_Z])
	{
		scnID = SCENE_ID_RULE;					// キーを押したらルールシーンに移動
	}
}


// ルール説明表示
//---------------------
void RuleDraw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	DrawBox(GAME_SCREEN_X, GAME_SCREEN_Y, GAME_SCREEN_X + GAME_SCREEN_SIZE_X, GAME_SCREEN_Y + GAME_SCREEN_SIZE_Y, GetColor(30, 30, 30), true);

	ScreenFlip();
}





// ゲーム画面
//---------------------
void GameScene(void)
{
	PlayerCtl();
	PshotCtl();
	EnemyCtl();
	CheckHitCtl();
	EshotCtl();

	GameDraw();
}


// 自機処理
//---------------------
void PlayerCtl(void)
{
	// 自機復帰処理
	//-------------------------
	if (!playerAlive)					// 自機がやられたとき
	{
		playerAlive = true;
	}
	// 自機移動処理
	//---------------------
	if (keyBuf[KEY_INPUT_RIGHT] == 1)
	{
		if (playerPosX + playerSpeed <= GAME_SCREEN_SIZE_X - PLAYER_SIZE_X)
		{
			playerPosX += playerSpeed;					// 右移動
		}
		else
		{
			playerPosX = GAME_SCREEN_SIZE_X - PLAYER_SIZE_X;		// 右移動制限
		}
	}
	if (keyBuf[KEY_INPUT_LEFT] == 1)
	{
		if (playerPosX - playerSpeed >= 0)
		{
			playerPosX -= playerSpeed;					// 左移動
		}
		else
		{
			playerPosX = 0;											// 左移動制限
		}
	}
}


// 自機の弾処理
//---------------------
void PshotCtl(void)
{
	if (!pShotAlive)					// 発射していないとき
	{
		if ((keyBuf[KEY_INPUT_Z] == 1) && (!keyBufOld[KEY_INPUT_Z]))
		{
			pShotAlive = true;
			pShotPosX = playerPosX + (PLAYER_SIZE_X / 2);
			pShotPosY = playerPosY;
		}
	}
	else
	{											// 発射しているとき
		pShotPosY -= pShotSpeed;
		if (pShotPosY <= 0)			// 画面外に行ったら
		{
			pShotAlive = false;
		}
		//if (keyBuf[KEY_INPUT_RIGHT])
		//{
		//	pShotPosX += pShotSpeed;
		//}
		//if (keyBuf[KEY_INPUT_LEFT])
		//{
		//	pShotPosX -= pShotSpeed;
		//}
		//if (keyBuf[KEY_INPUT_UP])
		//{
		//	pShotPosY -= pShotSpeed;
		//}
		//if (keyBuf[KEY_INPUT_DOWN])
		//{
		//	pShotPosY += pShotSpeed;
		//}
	}
}


// 敵処理
//------------------
void EnemyCtl(void)
{
	if (enemyAlive)
	{
		// 敵移動制御
		//---------------------
		if (enemyMoveMode == MOVE_MODE_DOWN)
		{
			// 敵下移動処理
			//---------------------
			dir = DIR_DOWN;										// 敵下方向転換アニメーション
			if (!(enemyMoveCnt % ENEMY_MOVE_INT))
			{
				if ((ENEMY_COUNT_Y - 1) - enemyMoveCnt < ENEMY_COUNT_Y)
				{
					for (x = 0; x < ENEMY_COUNT_X; x++)
					{
						enemyPosY[(ENEMY_COUNT_Y - 1) - (enemyMoveCnt / ENEMY_MOVE_INT)][x] += GET_ENEMY_POS_Y(1);
						enemyDir[(ENEMY_COUNT_Y - 1) - (enemyMoveCnt / ENEMY_MOVE_INT)][x] = DIR_DOWN;
						//enemyDir[y][(ENEMY_COUNT_X - 1) - ((enemyMoveCnt / ENEMY_MOVE_INT) % ENEMY_COUNT_X)] = DIR_DOWN;
					}
				}
			}
		}
		else
		{
			// 敵左右移動処理
			//---------------------
			if (!(enemyMoveCnt % ENEMY_MOVE_INT))
			{
				if ((ENEMY_COUNT_X - 1) - enemyMoveCnt < ENEMY_COUNT_X)
				{
					for (y = 0; y < ENEMY_COUNT_Y; y++)
					{
						if (enemyMoveCnt % 5 == 0)
						{
							if (enemyMoveFlagX == MOVE_RIGHT)
							{
								dir = DIR_RIGHT;						// 敵右方向転換アニメーション
								enemyPosX[y][(ENEMY_COUNT_X - 1) - ((enemyMoveCnt / ENEMY_MOVE_INT) % ENEMY_COUNT_X)] += enemySpeed;
								enemyDir[y][(ENEMY_COUNT_X - 1) - ((enemyMoveCnt / ENEMY_MOVE_INT) % ENEMY_COUNT_X)] = DIR_RIGHT;
							}
							else
							{
								dir = DIR_LEFT;							// 敵左方向転換アニメーション
								enemyPosX[y][(enemyMoveCnt / ENEMY_MOVE_INT) % ENEMY_COUNT_X] -= enemySpeed;
								enemyDir[y][(enemyMoveCnt / ENEMY_MOVE_INT) % ENEMY_COUNT_X] = DIR_LEFT;
								//enemyDir[y][(ENEMY_COUNT_X - 1) - ((enemyMoveCnt / ENEMY_MOVE_INT) % ENEMY_COUNT_X)] = DIR_LEFT;
							}
						}
					}
					// 敵の弾発射処理
					//---------------------
					for (x = 0; x < ENEMY_COUNT_X; x++)
					{
						if (!eShotAlive[x])
						{
							if ((rand() % 300) == 0)
							{
								for (y = ENEMY_COUNT_Y - 1; y >= 0; y--)
								{
									if (enemyAlive[y][x])
									{
										eShotPosX[x] = enemyPosX[y][x];
										eShotPosY[x] = enemyPosY[y][x];
										eShotAlive[x] = true;
										enemyDir[y][x] = DIR_DOWN;
										break;
									}
								}
							}
						}
					}
				}
			}
		}
		enemyMoveCnt++;

		// 敵下方向段階移動
		//---------------------
		if (enemyMoveMode == MOVE_MODE_DOWN)
		{
			if (enemyMoveCnt / ENEMY_MOVE_INT >= ENEMY_COUNT_Y)
			{
				enemyMoveCnt = 0;
				enemyMoveMode = MOVE_MODE_LR;
				CheckEnemyLine();
			}
		}
		else
		{
			CheckEnemyMoveLR();				// 敵方向転換確認
		}
	}


	//bool flag = false;	[誤例]
	//for (i = 0; i < ENEMY_COUNT_Y; i++)
	//{
	//	for (j = 0; j < ENEMY_COUNT_X; j++)
	//	{
	//		if (j == 4)
	//		{
	//			flag = true;
	//			break;				break...直近のforやwhileを１個だけ抜ける
	//		}
	//	}
	//	if (flag)
	//	{
	//		break;
	//	}
	//}
}


// 敵の防衛ライン到達確認
//---------------------
void CheckEnemyLine(void)
{
	//x = 0;
	//y = ENEMY_COUNT_Y - 1;

	// 敵の最下段位置のサーチ
	for (y = ENEMY_COUNT_Y - 1; y >= 0; y--)
	{
		for (x = 0; x < ENEMY_COUNT_X; x++)
		{
			if (enemyAlive[y][x])
			{
				goto END;
			}
		}
	}
	END:

	// サーチした最下段の敵が防衛ラインに到達しているかをチェックする
	if (enemyPosY[y][x] >= GET_ENEMY_POS_Y(ENEMY_COUNT_Y + 3))
	{
		if (DethProcPlayer())
		{
			for (y = 0; y < ENEMY_COUNT_Y; y++)
			{
				for (x = 0; x < ENEMY_COUNT_X; x++)
				{
					enemyPosY[y][x] -= GET_ENEMY_POS_Y(3);
				}
			}
		}
	}
}


// 自機の死亡時処理
//---------------------
bool DethProcPlayer(void)
{
	playerAlive = false;
	if (playerLife > 0)				// 残機が残ってるとき
	{
		playerLife--;			// 残機を減らす
		return true;
	}
									// 残機がなくなったとき（GAME OVER）
	scnID = SCENE_ID_GAMEOVER;			// ゲームオーバー画面へ移動
	return false;
}


// 敵方向転換確認						...敵移動と一緒に処理しない
//---------------------
void CheckEnemyMoveLR(void)
{
	// 敵左右方向段階移動
	//---------------------
	if (enemyMoveCnt % (5 * ENEMY_COUNT_X) != 0)
	{
		return;
	}

	//if (((enemyMoveCnt / ENEMY_MOVE_INT) % ENEMY_COUNT_X != 0) && (enemyMoveCnt % ENEMY_MOVE_INT) != ENEMY_MOVE_INT - 1)
	//{
	//	return;
	//}

	for (y = 0; y < ENEMY_COUNT_Y; y++)
	{
		for (x = 0; x < ENEMY_COUNT_X; x++)
		{
			if (enemyMoveFlagX == MOVE_RIGHT)
			{
				if (enemyPosX[y][x] >= GAME_SCREEN_SIZE_X - ENEMY_SIZE_X)		// 右端
				{
					enemyMoveFlagX = MOVE_LEFT;
					enemyMoveMode = MOVE_MODE_DOWN;
					enemyMoveCnt = 0;
					return;
				}
			}
			else
			{
				if (enemyPosX[y][x] <= 0)									// 左端
				{
					enemyMoveFlagX = MOVE_RIGHT;
					enemyMoveMode = MOVE_MODE_DOWN;
					enemyMoveCnt = 0;
					return;
				}
			}
		}
	}
}


// 敵の弾処理
//---------------------
void EshotCtl(void)
{
	for (x = 0; x < ENEMY_COUNT_X; x++)
	{
		if (!eShotAlive[x])					// 発射していないとき
		{
			continue;
			//if ((keyBuf[KEY_INPUT_Z] == 1) && (!keyBufOld[KEY_INPUT_Z]))
			//{
			//	eShotAlive[j] = true;
			//}
		}
		else								// 発射しているとき
		{
			eShotPosY[x] += pShotSpeed;
			if (eShotPosY[x] >= GAME_SCREEN_SIZE_Y - ENEMY_SHOT_SIZE_Y)
			{
				eShotAlive[x] = false;
			}
		}
	}
}


// 当たり判定処理
//---------------------
void CheckHitCtl(void)
{
	CheckHitPshotEnemy();
	CheckHitEshotPlayer();
}


// 自機の弾と敵の当たり判定処理
//---------------------
void CheckHitPshotEnemy(void)
{
	if (pShotAlive)
	{
		for (y = 0; y < ENEMY_COUNT_Y; y++)				// 行：横	列：縦
		{
			for (x = 0; x < ENEMY_COUNT_X; x++)
			{
				if (enemyAlive[y][x])
				{
					if ((pShotPosY <= enemyPosY[y][x] + ENEMY_SIZE_Y) && (pShotPosY + PLAYER_SHOT_SIZE_Y >= enemyPosY[y][x]) && (pShotPosX <= enemyPosX[y][x] + ENEMY_SIZE_X) && (pShotPosX + PLAYER_SHOT_SIZE_X >= enemyPosX[y][x]))
					{
						// 敵を倒した時の処理
						//---------------------
						AddScr(ENEMY_POINT);
						//scrData += ENEMY_POINT;			// スコア加算
						pShotAlive = false;
						enemyAlive[y][x] = false;
						//TRACE("当たり X:%d Y:%d\n",j,i);
						return;			// 2重for文を抜けるために無理やり関数を作る
					}
				}
			}
		}
	}
}


// 自機と敵の当たり判定処理
//---------------------
void CheckHitEshotPlayer(void)
{
	for ( n = 0; n < ENEMY_COUNT_X; n++)
	{
		if (eShotAlive[n])
		{
			if (playerAlive)
			{
				if ((eShotPosY[n] <= playerPosY + PLAYER_SIZE_Y) && (eShotPosY[n] + ENEMY_SHOT_SIZE_Y >= playerPosY) && (eShotPosX[n] <= playerPosX + PLAYER_SIZE_X) && (eShotPosX[n] + ENEMY_SHOT_SIZE_X >= playerPosX))
				{
					// 当たった時の処理
					//---------------------
					eShotAlive[n] = false;
					DethProcPlayer();
					//TRACE("当たり\n");
					return;
				}
			}
		}
	}
}


// 右スコア欄表示処理
//---------------------
void ScrDraw(void)
{
	DrawCount(2, "SCORE", scrData, "HI SCORE");
	DrawCount(6, "HI-SCORE", hiScrData, "HI-SCORE");
}


// スコア表示処理
//---------------------
void DrawCount(int rows, const char* str, int Cnt, const char* lenStr)
{
	DrawString(UI_DRAW_X, GAME_SCREEN_Y + GAME_FONT_SIZE * rows, str, 0xffffff);						// スコア表示
	int ScrWidth = GetDrawStringWidth(lenStr, strlen(lenStr));						// SCOREの文字の長さを取得
	int ScrCntWidth = GetDrawFormatStringWidth("%d", Cnt);							// scrDataの数値の長さを取得
	DrawFormatString(UI_DRAW_X + ScrWidth - ScrCntWidth, GAME_SCREEN_Y + GAME_FONT_SIZE * (rows + 1), 0xffffff, "%d", Cnt);					// スコア数字表示			座標に近いものから足していく
}


// スコア加算処理
//---------------------
bool AddScr(int num)
{
	scrData += num;					// スコア加算
	if (scrData > hiScrData)				// 現在のスコアがハイスコアを超えた場合
	{
		hiScrData = scrData;
	}
	return true;
}


// ゲーム描画処理
//---------------------
void GameDraw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);	// 描画する画面を裏の画面に設定
	ClearDrawScreen();				// 描画する画面の内容を消去

	DrawBox(GAME_SCREEN_X, GAME_SCREEN_Y, GAME_SCREEN_X + GAME_SCREEN_SIZE_X, GAME_SCREEN_Y + GAME_SCREEN_SIZE_Y, GetColor(30, 30, 30), true);

	//dir = DIR_DOWN;			// 敵下方向転換アニメーション
	//if (enemyMoveMode == MOVE_MODE_LR)
	//{
	//	if (enemyMoveFlagX == MOVE_RIGHT)
	//	{
	//		dir = DIR_RIGHT;			// 敵右方向転換アニメーション
	//	}
	//	else
	//	{
	//		dir = DIR_LEFT;				// 敵左方向転換アニメーション
	//	}
	//}

	DrawLine(GAME_SCREEN_X, GAME_SCREEN_Y + GET_ENEMY_POS_Y(ENEMY_COUNT_Y + 3), GAME_SCREEN_X + GAME_SCREEN_SIZE_X, GAME_SCREEN_Y + GET_ENEMY_POS_Y(ENEMY_COUNT_Y + 3), 0xffffff);

	for (n = 0; n < playerLife; n++)
	{
		DrawGraph(UI_DRAW_X + PLAYER_SIZE_X * n, GAME_SCREEN_Y + GAME_SCREEN_SIZE_Y - PLAYER_SIZE_Y, playerImage[DIR_DOWN][1], true);					// 残機表示
	}

	eAnimCnt = abs(((enemyAnimCnt / 10) % 4) - 2);						// 0.1.2.1.0.1.2.1.0........
	if ((eAnimCnt >= 0) && (eAnimCnt < ANIM_MAX))
	{
		for (y = 0; y < ENEMY_COUNT_Y; y++)				// 行：横	列：縦
		{
			for (x = 0; x < ENEMY_COUNT_X; x++)
			{
				if (enemyAlive[y][x] == true)
				{
					DrawGraph(GAME_SCREEN_X + enemyPosX[y][x], GAME_SCREEN_Y + enemyPosY[y][x], enemyImage[y % (ENEMY_TYPE_MAX - 1)][enemyDir[y][x]][eAnimCnt], true);
				}
			}
		}
	}

	if (pShotAlive)
	{
		DrawGraph(GAME_SCREEN_X + pShotPosX, GAME_SCREEN_Y + pShotPosY, pShotImage, true);
	}

	//_dbgDrawLine(SCREEN_SIZE_X / 2, 0, SCREEN_SIZE_X / 2, SCREEN_SIZE_Y, 0xff0000);
	//_dbgDrawPixel(SCREEN_SIZE_X / 2 - PLAYER_SIZE_X / 2, 0, playerImage[DIR_DOWN][2], true);
	pAnimCnt = abs(((playerAnimCnt / 15) % 4) - 2);							// 0.1.2.1.0.1.2.1.0........
	if ((pAnimCnt >= 0) && (pAnimCnt < ANIM_MAX))
	{
		DrawGraph(GAME_SCREEN_X + playerPosX, GAME_SCREEN_Y + playerPosY, playerImage[DIR_UP][pAnimCnt], true);
	}

	for (x = 0; x < ENEMY_COUNT_X; x++)
	{
		if (eShotAlive[x])					// 自機より優先度高め
		{
			DrawGraph(GAME_SCREEN_X + eShotPosX[x], GAME_SCREEN_Y + eShotPosY[x], eShotImage, true);
		}
	}

	ScrDraw();

	//DrawString(GAME_SCREEN_X + GAME_SCREEN_SIZE_X + 30, GAME_SCREEN_Y + GAME_FONT_SIZE, "SCORE", 0xffffff);						// スコア表示
	//int ScrWidth = GetDrawStringWidth("HI SCORE", strlen("HI SCORE"));						// SCOREの文字の長さを取得
	//int ScrCntWidth = GetDrawFormatStringWidth("%d", scrData);							// scrDataの数値の長さを取得
	//DrawFormatString(GAME_SCREEN_X + GAME_SCREEN_SIZE_X + 30 + ScrWidth - ScrCntWidth, GAME_SCREEN_Y + GAME_FONT_SIZE * 2, 0xffffff, "%d", scrData);					// スコア数字表示			座標に近いものから足していく
	//DrawString(GAME_SCREEN_X + GAME_SCREEN_SIZE_X + 30, GAME_SCREEN_Y + GAME_FONT_SIZE * 5, "HI SCORE", 0xffffff);
	//int ScrWidth = GetDrawStringWidth(lenStr, strlen("HI SCORE"));
	//int ScrCntWidth = GetDrawFormatStringWidth("%d", hiScrData);
	//DrawFormatString(GAME_SCREEN_X + GAME_SCREEN_SIZE_X + 30 + ScrWidth - ScrCntWidth, GAME_SCREEN_Y + GAME_FONT_SIZE * 6, 0xffffff, "%d", hiScrData);

	_dbgAddDraw();
	ScreenFlip();			// 裏の画面を表の画面に瞬間コピー

	enemyAnimCnt++;
	playerAnimCnt++;
}





// ゲームオーバー画面
//---------------------
void GameOverScene(void)
{
	GameOverDraw();

	if (gameOverCnt == 2)
	{
		if (keyBuf[KEY_INPUT_Z] && !keyBufOld[KEY_INPUT_Z])
		{
			GameInit();
			scnID = SCENE_ID_GAME;
		}
	}
	if (gameOverCnt == 4)
	{
		if (keyBuf[KEY_INPUT_Z] && !keyBufOld[KEY_INPUT_Z])
		{
			scnID = SCENE_ID_TITLE;
		}
	}
}


// ゲームオーバー描画処理
//---------------------
void GameOverDraw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();


	DrawBox(GAME_SCREEN_X, GAME_SCREEN_Y, GAME_SCREEN_X + GAME_SCREEN_SIZE_X, GAME_SCREEN_Y + GAME_SCREEN_SIZE_Y, GetColor(30, 30, 30), true);

	DrawGraph(gameOverPosX, gameOverPosY, gameOverImage, true);					// ゲームオーバーロゴ描画

	int ScrWidth = GetDrawStringWidth("CONTINUE?", strlen("CONTINUE?"));
	DrawString(GAME_SCREEN_X + (GAME_SCREEN_SIZE_X - ScrWidth) / 2, GAME_SCREEN_Y + (GAME_SCREEN_SIZE_Y / 2) + GAME_FONT_SIZE, "CONTINUE?",0xff0000);					// "CONTINUE?"の文字列を描画

	ScrWidth = GetDrawStringWidth("YES", strlen("YES"));
	DrawString(GAME_SCREEN_X + (GAME_SCREEN_SIZE_X - ScrWidth) / 2, GAME_SCREEN_Y + (GAME_SCREEN_SIZE_Y * 2 / 3) + GAME_FONT_SIZE * 2, "YES", 0x00ff00);				// "YES"の文字列を描画
	ScrWidth = GetDrawStringWidth("NO", strlen("NO"));
	DrawString(GAME_SCREEN_X + (GAME_SCREEN_SIZE_X - ScrWidth) / 2, GAME_SCREEN_Y + (GAME_SCREEN_SIZE_Y * 2 / 3) + GAME_FONT_SIZE * 4, "NO", 0x00ff00);					// "NO"の文字列を描画

	if ((blinkCnt / 30) % 2)
	{
		ScrWidth = GetDrawStringWidth("⇒", strlen("⇒"));
		DrawString(GAME_SCREEN_X + (GAME_SCREEN_SIZE_X - ScrWidth) / 2 - 30, GAME_SCREEN_Y + (GAME_SCREEN_SIZE_Y * 2 / 3) + GAME_FONT_SIZE * gameOverCnt, "⇒", 0x00ff00);			// "⇒"の文字列を描画

	}
	if (keyBuf[KEY_INPUT_UP] && !keyBufOld[KEY_INPUT_UP])
	{
		gameOverCnt = 2;
	}
	if (keyBuf[KEY_INPUT_DOWN] && !keyBufOld[KEY_INPUT_DOWN])
	{
		gameOverCnt = 4;
	}

	ScrDraw();

	ScreenFlip();

	blinkCnt++;
}










// システム系処理
//---------------------
bool SysInit(void)
{
	// システム処理
	//-------------------
	SetWindowText("インベーダー");	// ゲームウィンドウのタイトル
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);			// ゲームウィンドウのサイズと色モードを設定
	ChangeWindowMode(true);				// ゲームウィンドウの表示方法 (true : window     false : フルスクリーン)
	if (DxLib_Init() == -1)				// DXライブラリの初期化処理		Init:イニシャライズ
	{
		//	TRACE("DxLib の初期化失敗");
		return false;						// DXライブラリの初期化失敗の為システム終了
	}

	srand((unsigned int)time(NULL));

	memset(keyBuf, 0, sizeof(keyBuf));					// keyBufすべてに０をセット		要素数 sizeof(keyBuf) * バイト数 sizeof(keyBuf[0])
	memset(keyBufOld, 0, sizeof(keyBufOld));

	//for (n = 0; n < 256; n++)				// memsetの処理と同義
	//{
	//	keyBuf[n] = 0;
	//	keyBufOld[n] = 0;
	//}

	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 255);

	// グラフィックの登録
	//--------------------
	const char* enemyFileName[ENEMY_TYPE_MAX] = {
		"image/Enemy 15-1.png",
		"image/Enemy 15-2.png",
		"image/Enemy 15-3.png",
		"image/Enemy 15-4.png",
		"image/Enemy 15-5.png",
		"image/Enemy 15-6.png",
		"image/Enemy 09-1.png"
	};

	titleImage = LoadGraph("image/TitleLogo2.png");				// タイトル画像読み込み
	if (titleImage == -1)
	{
		TRACE("タイトル画像の読み込みに失敗しました")
	}

	gameOverImage = LoadGraph("image/GameOver.png");
	if (gameOverImage == -1)
	{
		TRACE("ゲームオーバー画像の読み込みに失敗しました")
	}

	for (n = 0; n < ENEMY_TYPE_MAX; n++)
	{
		if (LoadDivGraph(enemyFileName[n], ANIM_MAX * DIR_MAX, ANIM_MAX, DIR_MAX, ENEMY_SIZE_X, ENEMY_SIZE_Y, &enemyImage[n][0][0]) == -1)
		{
			return false;
		}
	}

	pShotImage = LoadGraph("image/pshot.png");
	if (pShotImage == -1)
	{
		TRACE("弾画像の読み込みに失敗しました");
	}
											// 値渡し																// ポインター渡し
	if (LoadDivGraph("image/Male 05-1.png", ANIM_MAX * DIR_MAX, ANIM_MAX, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, &playerImage[0][0]) == -1)
	{
		return false;
	}

	eShotImage = LoadGraph("image/eshot.png");
	if (eShotImage == -1)
	{
		TRACE("弾画像の読み込みに失敗しました");
	}

	// 変数の初期化
	//--------------------
	scnID = SCENE_ID_TITLE;							// 初期シーン設定

	scrData = 0;						// 初期スコアデータ
	hiScrData = 2000;					// ハイスコアデータ

	blinkCnt = 0;				// 点滅表示カウンタ
	SetFontSize (GAME_FONT_SIZE);		// フォントサイズ設定

	titlePosX = GAME_SCREEN_X + ((GAME_SCREEN_SIZE_X - TITLE_SIZE_X) / 2);
	titlePosY = GAME_SCREEN_Y + ((GAME_SCREEN_SIZE_Y - TITLE_SIZE_Y) / 3);

	gameOverPosX = GAME_SCREEN_X + ((GAME_SCREEN_SIZE_X - GAMEOVER_SIZE_X) / 2);
	gameOverPosY = GAME_SCREEN_Y + ((GAME_SCREEN_SIZE_Y - GAMEOVER_SIZE_Y) / 4);


	return true;
}



// ゲームシステム系処理
//---------------------
bool GameInit(void)
{
	// 変数の初期化
	//--------------------
	n = 0;

	scrData = 0;						// 初期スコアデータ

	gameOverCnt = 2;

	playerPosX = (GAME_SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
	playerPosY = GAME_SCREEN_SIZE_Y - PLAYER_SIZE_Y;
	playerAlive = true;
	playerSpeed = 4;
	playerAnimCnt = 0;
	playerLife = 2;						// 現在の自機とは別に2体　＝　３体

	for (y = 0; y < ENEMY_COUNT_Y; y++)
	{
		for (x = 0; x < ENEMY_COUNT_X; x++)
		{
			enemyPosX[y][x] = (x * ENEMY_SIZE_X) * 3 / 2;
			enemyPosY[y][x] = GET_ENEMY_POS_Y(y + 2);
			enemyAlive[y][x] = true;
			enemyDir[y][x] = DIR_DOWN;
		}
	}
	enemySpeed = 17;
	enemyMoveCnt = 0;
	enemyAnimCnt = 0;
	enemyMoveFlagX = MOVE_RIGHT;
	enemyMoveMode = MOVE_MODE_LR;

	pShotPosX = 0;
	pShotPosY = 0;
	pShotAlive = false;
	pShotSpeed = 6;

	for (x = 0; x < ENEMY_COUNT_X; x++)
	{
		eShotPosX[x] = 0;
		eShotPosY[x] = 0;
		eShotAlive[x] = false;
	}
	eShotSpeed = 3;


	return true;
}
