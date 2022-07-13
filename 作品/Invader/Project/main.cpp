//---------------------------------
// �Q�[������F��{�\�[�X
// �����@�@�@�F2016010 �������l
//---------------------------------

#include "time.h"
#include "DxLib.h"			// DX���C�u�����̎g�p
#include "main.h"
#include "_debug/_DebugDispOut.h"
#include "_debug/_DebugConOut.h"

// �ϐ���`
//-----------------
int y, x, n;

int blinkCnt;										// �_�ŕ\���J�E���^

// �V�[���֌W
//-----------------
SCENE_ID scnID;										// ���݂̃V�[��

// �L�[�o�b�t�@
//-----------------
char keyBuf[256];
char keyBufOld[256];

// �^�C�g���֌W
//-----------------
int titleImage;										// �O���t�B�b�N�n���h��
int titlePosX;										// X���W
int titlePosY;										// Y���W

// �Q�[���I�[�o�[�֌W
//-----------------
int gameOverImage;									// �O���t�B�b�N�n���h��
int gameOverPosX;									// X���W
int gameOverPosY;									// Y���W
int gameOverCnt;									// ���Y���W

// �X�R�A�֌W
//-----------------
int scrData;										// ���݂̃X�R�A						�̂̓X�R�A��500�Ƃ�����A��2����00�͉�ʕ\���݂̂ɂ��āA�������ɂ�5�݂̂��i�[���邱�ƂŃ������̐ߖ���s����
int hiScrData;										// �n�C�X�R�A

// ���@�֌W
//-----------------
int playerImage[DIR_MAX][ANIM_MAX];					// �O���t�B�b�N�n���h��
int playerPosX;										// X���W
int playerPosY;										// Y���W
int playerSpeed;									// �ړ���
bool playerAlive;									// �����t���O
int playerAnimCnt;									// �A�j���[�V�����t���O
int pAnimCnt;										// �A�j���[�V�����J�E���^
int playerLife;										// ���@�̎c�@��						int�ł�char�ł�OK

// �G�֌W
//-----------------
int enemyImage[ENEMY_TYPE_MAX][DIR_MAX][ANIM_MAX];	// �O���t�B�b�N�n���h��
int enemyPosX[ENEMY_COUNT_Y][ENEMY_COUNT_X];		// X���W
int enemyPosY[ENEMY_COUNT_Y][ENEMY_COUNT_X];		// Y���W
DIR_ID enemyDir[ENEMY_COUNT_Y][ENEMY_COUNT_X];		// �G�̔��˕���
int enemySpeed;										// �ړ���
bool enemyAlive[ENEMY_COUNT_Y][ENEMY_COUNT_X];		// �����t���O
int enemyMoveCnt;									// �G�̈ړ��J�E���^
int enemyAnimCnt;									// �A�j���[�V�����t���O
int eAnimCnt;										// �A�j���[�V�����J�E���^
MOVE_LR enemyMoveFlagX;								// �G�̍��E�ړ��Ǘ��p
MOVE_MODE enemyMoveMode;							// �G�̍��E�ړ������ړ��̊Ǘ��p
DIR_ID dir;											// �G�����]���A�j���[�V����

// ���@�̒e�֌W
//-----------------
int pShotImage;										// �O���t�B�b�N�n���h��
int pShotPosX;										// X���W
int pShotPosY;										// Y���W
int pShotSpeed;										// �ړ���
bool pShotAlive;									// ���˃t���O

// �G�̒e�֌W
//-----------------
int eShotImage;										// �O���t�B�b�N�n���h��
int eShotPosX[ENEMY_COUNT_X];						// X���W
int eShotPosY[ENEMY_COUNT_X];						// Y���W
int eShotSpeed;										// �ړ���
bool eShotAlive[ENEMY_COUNT_X];						// ���˃t���O

// WinMain�֐�
//-----------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!SysInit())
	{
		TRACE("���������s");
		return -1;
	}


	// �Q�[�����[�v
	//---------------------
	while (ProcessMessage() == 0 && keyBuf[KEY_INPUT_ESCAPE] == 0)
	{
		//for (n = 0; 0 < 256; n++)					// memcpy�̏����Ɠ��`
		//{
		//	keyBufOld[n] = keyBuf[n];
		//}

		memcpy(keyBufOld, keyBuf, sizeof(keyBufOld));			// sizeof(keyBufOld) / sizeof(keyBufOld[0])
		GetHitKeyStateAll(keyBuf);

		_dbgStartDraw();


		// �V�[���ݒ菈��
		//---------------------
		switch (scnID)							// ����l��case�ł��ׂď���.....�ُ�l�Ɛ���l�����݂����Ă��܂�����  >>   switch�͂�����o�ł����(�s�𖳑ʂɎg������)
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
	
	// �V�X�e���I������
	//--------------------
	DxLib::DxLib_End();		// DX���C�u�����̏I������
	return 0;		// �Q�[���̏I��
}







// �^�C�g�����
//---------------------
void TitleScene(void)
{
	TitleDraw();

	if (keyBuf[KEY_INPUT_Z] && !keyBufOld[KEY_INPUT_Z])
	{
		GameInit();
		scnID = SCENE_ID_GAME;					// �L�[����������Q�[���V�[���Ɉړ�
	}
}


// �^�C�g���`�揈��
//---------------------
void TitleDraw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();


	DrawBox(GAME_SCREEN_X, GAME_SCREEN_Y, GAME_SCREEN_X + GAME_SCREEN_SIZE_X, GAME_SCREEN_Y + GAME_SCREEN_SIZE_Y, GetColor(30, 30, 30), true);

	DrawGraph(titlePosX, titlePosY, titleImage, true);					// �^�C�g�����S�`��

	if ((blinkCnt / 30) % 2)
	{
		int ScrWidth = GetDrawStringWidth("PHSH Z KEY", strlen("PHSH Z KEY"));
		DrawString(GAME_SCREEN_X + (GAME_SCREEN_SIZE_X - ScrWidth) / 2, GAME_SCREEN_Y + (GAME_SCREEN_SIZE_Y * 2 / 3), "PUSH Z KEY", 0x00ff00);				// "PHSH Z KEY"�̕������`��
	}

	ScrDraw();

	ScreenFlip();

	blinkCnt++;
}


// ���[�������p���
//---------------------
void RuleScene(void)
{
	RuleDraw();

	if (keyBuf[KEY_INPUT_Z] && !keyBufOld[KEY_INPUT_Z])
	{
		scnID = SCENE_ID_RULE;					// �L�[���������烋�[���V�[���Ɉړ�
	}
}


// ���[�������\��
//---------------------
void RuleDraw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	DrawBox(GAME_SCREEN_X, GAME_SCREEN_Y, GAME_SCREEN_X + GAME_SCREEN_SIZE_X, GAME_SCREEN_Y + GAME_SCREEN_SIZE_Y, GetColor(30, 30, 30), true);

	ScreenFlip();
}





// �Q�[�����
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


// ���@����
//---------------------
void PlayerCtl(void)
{
	// ���@���A����
	//-------------------------
	if (!playerAlive)					// ���@�����ꂽ�Ƃ�
	{
		playerAlive = true;
	}
	// ���@�ړ�����
	//---------------------
	if (keyBuf[KEY_INPUT_RIGHT] == 1)
	{
		if (playerPosX + playerSpeed <= GAME_SCREEN_SIZE_X - PLAYER_SIZE_X)
		{
			playerPosX += playerSpeed;					// �E�ړ�
		}
		else
		{
			playerPosX = GAME_SCREEN_SIZE_X - PLAYER_SIZE_X;		// �E�ړ�����
		}
	}
	if (keyBuf[KEY_INPUT_LEFT] == 1)
	{
		if (playerPosX - playerSpeed >= 0)
		{
			playerPosX -= playerSpeed;					// ���ړ�
		}
		else
		{
			playerPosX = 0;											// ���ړ�����
		}
	}
}


// ���@�̒e����
//---------------------
void PshotCtl(void)
{
	if (!pShotAlive)					// ���˂��Ă��Ȃ��Ƃ�
	{
		if ((keyBuf[KEY_INPUT_Z] == 1) && (!keyBufOld[KEY_INPUT_Z]))
		{
			pShotAlive = true;
			pShotPosX = playerPosX + (PLAYER_SIZE_X / 2);
			pShotPosY = playerPosY;
		}
	}
	else
	{											// ���˂��Ă���Ƃ�
		pShotPosY -= pShotSpeed;
		if (pShotPosY <= 0)			// ��ʊO�ɍs������
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


// �G����
//------------------
void EnemyCtl(void)
{
	if (enemyAlive)
	{
		// �G�ړ�����
		//---------------------
		if (enemyMoveMode == MOVE_MODE_DOWN)
		{
			// �G���ړ�����
			//---------------------
			dir = DIR_DOWN;										// �G�������]���A�j���[�V����
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
			// �G���E�ړ�����
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
								dir = DIR_RIGHT;						// �G�E�����]���A�j���[�V����
								enemyPosX[y][(ENEMY_COUNT_X - 1) - ((enemyMoveCnt / ENEMY_MOVE_INT) % ENEMY_COUNT_X)] += enemySpeed;
								enemyDir[y][(ENEMY_COUNT_X - 1) - ((enemyMoveCnt / ENEMY_MOVE_INT) % ENEMY_COUNT_X)] = DIR_RIGHT;
							}
							else
							{
								dir = DIR_LEFT;							// �G�������]���A�j���[�V����
								enemyPosX[y][(enemyMoveCnt / ENEMY_MOVE_INT) % ENEMY_COUNT_X] -= enemySpeed;
								enemyDir[y][(enemyMoveCnt / ENEMY_MOVE_INT) % ENEMY_COUNT_X] = DIR_LEFT;
								//enemyDir[y][(ENEMY_COUNT_X - 1) - ((enemyMoveCnt / ENEMY_MOVE_INT) % ENEMY_COUNT_X)] = DIR_LEFT;
							}
						}
					}
					// �G�̒e���ˏ���
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

		// �G�������i�K�ړ�
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
			CheckEnemyMoveLR();				// �G�����]���m�F
		}
	}


	//bool flag = false;	[���]
	//for (i = 0; i < ENEMY_COUNT_Y; i++)
	//{
	//	for (j = 0; j < ENEMY_COUNT_X; j++)
	//	{
	//		if (j == 4)
	//		{
	//			flag = true;
	//			break;				break...���߂�for��while���P����������
	//		}
	//	}
	//	if (flag)
	//	{
	//		break;
	//	}
	//}
}


// �G�̖h�q���C�����B�m�F
//---------------------
void CheckEnemyLine(void)
{
	//x = 0;
	//y = ENEMY_COUNT_Y - 1;

	// �G�̍ŉ��i�ʒu�̃T�[�`
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

	// �T�[�`�����ŉ��i�̓G���h�q���C���ɓ��B���Ă��邩���`�F�b�N����
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


// ���@�̎��S������
//---------------------
bool DethProcPlayer(void)
{
	playerAlive = false;
	if (playerLife > 0)				// �c�@���c���Ă�Ƃ�
	{
		playerLife--;			// �c�@�����炷
		return true;
	}
									// �c�@���Ȃ��Ȃ����Ƃ��iGAME OVER�j
	scnID = SCENE_ID_GAMEOVER;			// �Q�[���I�[�o�[��ʂֈړ�
	return false;
}


// �G�����]���m�F						...�G�ړ��ƈꏏ�ɏ������Ȃ�
//---------------------
void CheckEnemyMoveLR(void)
{
	// �G���E�����i�K�ړ�
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
				if (enemyPosX[y][x] >= GAME_SCREEN_SIZE_X - ENEMY_SIZE_X)		// �E�[
				{
					enemyMoveFlagX = MOVE_LEFT;
					enemyMoveMode = MOVE_MODE_DOWN;
					enemyMoveCnt = 0;
					return;
				}
			}
			else
			{
				if (enemyPosX[y][x] <= 0)									// ���[
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


// �G�̒e����
//---------------------
void EshotCtl(void)
{
	for (x = 0; x < ENEMY_COUNT_X; x++)
	{
		if (!eShotAlive[x])					// ���˂��Ă��Ȃ��Ƃ�
		{
			continue;
			//if ((keyBuf[KEY_INPUT_Z] == 1) && (!keyBufOld[KEY_INPUT_Z]))
			//{
			//	eShotAlive[j] = true;
			//}
		}
		else								// ���˂��Ă���Ƃ�
		{
			eShotPosY[x] += pShotSpeed;
			if (eShotPosY[x] >= GAME_SCREEN_SIZE_Y - ENEMY_SHOT_SIZE_Y)
			{
				eShotAlive[x] = false;
			}
		}
	}
}


// �����蔻�菈��
//---------------------
void CheckHitCtl(void)
{
	CheckHitPshotEnemy();
	CheckHitEshotPlayer();
}


// ���@�̒e�ƓG�̓����蔻�菈��
//---------------------
void CheckHitPshotEnemy(void)
{
	if (pShotAlive)
	{
		for (y = 0; y < ENEMY_COUNT_Y; y++)				// �s�F��	��F�c
		{
			for (x = 0; x < ENEMY_COUNT_X; x++)
			{
				if (enemyAlive[y][x])
				{
					if ((pShotPosY <= enemyPosY[y][x] + ENEMY_SIZE_Y) && (pShotPosY + PLAYER_SHOT_SIZE_Y >= enemyPosY[y][x]) && (pShotPosX <= enemyPosX[y][x] + ENEMY_SIZE_X) && (pShotPosX + PLAYER_SHOT_SIZE_X >= enemyPosX[y][x]))
					{
						// �G��|�������̏���
						//---------------------
						AddScr(ENEMY_POINT);
						//scrData += ENEMY_POINT;			// �X�R�A���Z
						pShotAlive = false;
						enemyAlive[y][x] = false;
						//TRACE("������ X:%d Y:%d\n",j,i);
						return;			// 2�dfor���𔲂��邽�߂ɖ������֐������
					}
				}
			}
		}
	}
}


// ���@�ƓG�̓����蔻�菈��
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
					// �����������̏���
					//---------------------
					eShotAlive[n] = false;
					DethProcPlayer();
					//TRACE("������\n");
					return;
				}
			}
		}
	}
}


// �E�X�R�A���\������
//---------------------
void ScrDraw(void)
{
	DrawCount(2, "SCORE", scrData, "HI SCORE");
	DrawCount(6, "HI-SCORE", hiScrData, "HI-SCORE");
}


// �X�R�A�\������
//---------------------
void DrawCount(int rows, const char* str, int Cnt, const char* lenStr)
{
	DrawString(UI_DRAW_X, GAME_SCREEN_Y + GAME_FONT_SIZE * rows, str, 0xffffff);						// �X�R�A�\��
	int ScrWidth = GetDrawStringWidth(lenStr, strlen(lenStr));						// SCORE�̕����̒������擾
	int ScrCntWidth = GetDrawFormatStringWidth("%d", Cnt);							// scrData�̐��l�̒������擾
	DrawFormatString(UI_DRAW_X + ScrWidth - ScrCntWidth, GAME_SCREEN_Y + GAME_FONT_SIZE * (rows + 1), 0xffffff, "%d", Cnt);					// �X�R�A�����\��			���W�ɋ߂����̂��瑫���Ă���
}


// �X�R�A���Z����
//---------------------
bool AddScr(int num)
{
	scrData += num;					// �X�R�A���Z
	if (scrData > hiScrData)				// ���݂̃X�R�A���n�C�X�R�A�𒴂����ꍇ
	{
		hiScrData = scrData;
	}
	return true;
}


// �Q�[���`�揈��
//---------------------
void GameDraw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);	// �`�悷���ʂ𗠂̉�ʂɐݒ�
	ClearDrawScreen();				// �`�悷���ʂ̓��e������

	DrawBox(GAME_SCREEN_X, GAME_SCREEN_Y, GAME_SCREEN_X + GAME_SCREEN_SIZE_X, GAME_SCREEN_Y + GAME_SCREEN_SIZE_Y, GetColor(30, 30, 30), true);

	//dir = DIR_DOWN;			// �G�������]���A�j���[�V����
	//if (enemyMoveMode == MOVE_MODE_LR)
	//{
	//	if (enemyMoveFlagX == MOVE_RIGHT)
	//	{
	//		dir = DIR_RIGHT;			// �G�E�����]���A�j���[�V����
	//	}
	//	else
	//	{
	//		dir = DIR_LEFT;				// �G�������]���A�j���[�V����
	//	}
	//}

	DrawLine(GAME_SCREEN_X, GAME_SCREEN_Y + GET_ENEMY_POS_Y(ENEMY_COUNT_Y + 3), GAME_SCREEN_X + GAME_SCREEN_SIZE_X, GAME_SCREEN_Y + GET_ENEMY_POS_Y(ENEMY_COUNT_Y + 3), 0xffffff);

	for (n = 0; n < playerLife; n++)
	{
		DrawGraph(UI_DRAW_X + PLAYER_SIZE_X * n, GAME_SCREEN_Y + GAME_SCREEN_SIZE_Y - PLAYER_SIZE_Y, playerImage[DIR_DOWN][1], true);					// �c�@�\��
	}

	eAnimCnt = abs(((enemyAnimCnt / 10) % 4) - 2);						// 0.1.2.1.0.1.2.1.0........
	if ((eAnimCnt >= 0) && (eAnimCnt < ANIM_MAX))
	{
		for (y = 0; y < ENEMY_COUNT_Y; y++)				// �s�F��	��F�c
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
		if (eShotAlive[x])					// ���@���D��x����
		{
			DrawGraph(GAME_SCREEN_X + eShotPosX[x], GAME_SCREEN_Y + eShotPosY[x], eShotImage, true);
		}
	}

	ScrDraw();

	//DrawString(GAME_SCREEN_X + GAME_SCREEN_SIZE_X + 30, GAME_SCREEN_Y + GAME_FONT_SIZE, "SCORE", 0xffffff);						// �X�R�A�\��
	//int ScrWidth = GetDrawStringWidth("HI SCORE", strlen("HI SCORE"));						// SCORE�̕����̒������擾
	//int ScrCntWidth = GetDrawFormatStringWidth("%d", scrData);							// scrData�̐��l�̒������擾
	//DrawFormatString(GAME_SCREEN_X + GAME_SCREEN_SIZE_X + 30 + ScrWidth - ScrCntWidth, GAME_SCREEN_Y + GAME_FONT_SIZE * 2, 0xffffff, "%d", scrData);					// �X�R�A�����\��			���W�ɋ߂����̂��瑫���Ă���
	//DrawString(GAME_SCREEN_X + GAME_SCREEN_SIZE_X + 30, GAME_SCREEN_Y + GAME_FONT_SIZE * 5, "HI SCORE", 0xffffff);
	//int ScrWidth = GetDrawStringWidth(lenStr, strlen("HI SCORE"));
	//int ScrCntWidth = GetDrawFormatStringWidth("%d", hiScrData);
	//DrawFormatString(GAME_SCREEN_X + GAME_SCREEN_SIZE_X + 30 + ScrWidth - ScrCntWidth, GAME_SCREEN_Y + GAME_FONT_SIZE * 6, 0xffffff, "%d", hiScrData);

	_dbgAddDraw();
	ScreenFlip();			// ���̉�ʂ�\�̉�ʂɏu�ԃR�s�[

	enemyAnimCnt++;
	playerAnimCnt++;
}





// �Q�[���I�[�o�[���
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


// �Q�[���I�[�o�[�`�揈��
//---------------------
void GameOverDraw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();


	DrawBox(GAME_SCREEN_X, GAME_SCREEN_Y, GAME_SCREEN_X + GAME_SCREEN_SIZE_X, GAME_SCREEN_Y + GAME_SCREEN_SIZE_Y, GetColor(30, 30, 30), true);

	DrawGraph(gameOverPosX, gameOverPosY, gameOverImage, true);					// �Q�[���I�[�o�[���S�`��

	int ScrWidth = GetDrawStringWidth("CONTINUE?", strlen("CONTINUE?"));
	DrawString(GAME_SCREEN_X + (GAME_SCREEN_SIZE_X - ScrWidth) / 2, GAME_SCREEN_Y + (GAME_SCREEN_SIZE_Y / 2) + GAME_FONT_SIZE, "CONTINUE?",0xff0000);					// "CONTINUE?"�̕������`��

	ScrWidth = GetDrawStringWidth("YES", strlen("YES"));
	DrawString(GAME_SCREEN_X + (GAME_SCREEN_SIZE_X - ScrWidth) / 2, GAME_SCREEN_Y + (GAME_SCREEN_SIZE_Y * 2 / 3) + GAME_FONT_SIZE * 2, "YES", 0x00ff00);				// "YES"�̕������`��
	ScrWidth = GetDrawStringWidth("NO", strlen("NO"));
	DrawString(GAME_SCREEN_X + (GAME_SCREEN_SIZE_X - ScrWidth) / 2, GAME_SCREEN_Y + (GAME_SCREEN_SIZE_Y * 2 / 3) + GAME_FONT_SIZE * 4, "NO", 0x00ff00);					// "NO"�̕������`��

	if ((blinkCnt / 30) % 2)
	{
		ScrWidth = GetDrawStringWidth("��", strlen("��"));
		DrawString(GAME_SCREEN_X + (GAME_SCREEN_SIZE_X - ScrWidth) / 2 - 30, GAME_SCREEN_Y + (GAME_SCREEN_SIZE_Y * 2 / 3) + GAME_FONT_SIZE * gameOverCnt, "��", 0x00ff00);			// "��"�̕������`��

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










// �V�X�e���n����
//---------------------
bool SysInit(void)
{
	// �V�X�e������
	//-------------------
	SetWindowText("�C���x�[�_�[");	// �Q�[���E�B���h�E�̃^�C�g��
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);			// �Q�[���E�B���h�E�̃T�C�Y�ƐF���[�h��ݒ�
	ChangeWindowMode(true);				// �Q�[���E�B���h�E�̕\�����@ (true : window     false : �t���X�N���[��)
	if (DxLib_Init() == -1)				// DX���C�u�����̏���������		Init:�C�j�V�����C�Y
	{
		//	TRACE("DxLib �̏��������s");
		return false;						// DX���C�u�����̏��������s�̈׃V�X�e���I��
	}

	srand((unsigned int)time(NULL));

	memset(keyBuf, 0, sizeof(keyBuf));					// keyBuf���ׂĂɂO���Z�b�g		�v�f�� sizeof(keyBuf) * �o�C�g�� sizeof(keyBuf[0])
	memset(keyBufOld, 0, sizeof(keyBufOld));

	//for (n = 0; n < 256; n++)				// memset�̏����Ɠ��`
	//{
	//	keyBuf[n] = 0;
	//	keyBufOld[n] = 0;
	//}

	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 255);

	// �O���t�B�b�N�̓o�^
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

	titleImage = LoadGraph("image/TitleLogo2.png");				// �^�C�g���摜�ǂݍ���
	if (titleImage == -1)
	{
		TRACE("�^�C�g���摜�̓ǂݍ��݂Ɏ��s���܂���")
	}

	gameOverImage = LoadGraph("image/GameOver.png");
	if (gameOverImage == -1)
	{
		TRACE("�Q�[���I�[�o�[�摜�̓ǂݍ��݂Ɏ��s���܂���")
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
		TRACE("�e�摜�̓ǂݍ��݂Ɏ��s���܂���");
	}
											// �l�n��																// �|�C���^�[�n��
	if (LoadDivGraph("image/Male 05-1.png", ANIM_MAX * DIR_MAX, ANIM_MAX, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, &playerImage[0][0]) == -1)
	{
		return false;
	}

	eShotImage = LoadGraph("image/eshot.png");
	if (eShotImage == -1)
	{
		TRACE("�e�摜�̓ǂݍ��݂Ɏ��s���܂���");
	}

	// �ϐ��̏�����
	//--------------------
	scnID = SCENE_ID_TITLE;							// �����V�[���ݒ�

	scrData = 0;						// �����X�R�A�f�[�^
	hiScrData = 2000;					// �n�C�X�R�A�f�[�^

	blinkCnt = 0;				// �_�ŕ\���J�E���^
	SetFontSize (GAME_FONT_SIZE);		// �t�H���g�T�C�Y�ݒ�

	titlePosX = GAME_SCREEN_X + ((GAME_SCREEN_SIZE_X - TITLE_SIZE_X) / 2);
	titlePosY = GAME_SCREEN_Y + ((GAME_SCREEN_SIZE_Y - TITLE_SIZE_Y) / 3);

	gameOverPosX = GAME_SCREEN_X + ((GAME_SCREEN_SIZE_X - GAMEOVER_SIZE_X) / 2);
	gameOverPosY = GAME_SCREEN_Y + ((GAME_SCREEN_SIZE_Y - GAMEOVER_SIZE_Y) / 4);


	return true;
}



// �Q�[���V�X�e���n����
//---------------------
bool GameInit(void)
{
	// �ϐ��̏�����
	//--------------------
	n = 0;

	scrData = 0;						// �����X�R�A�f�[�^

	gameOverCnt = 2;

	playerPosX = (GAME_SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
	playerPosY = GAME_SCREEN_SIZE_Y - PLAYER_SIZE_Y;
	playerAlive = true;
	playerSpeed = 4;
	playerAnimCnt = 0;
	playerLife = 2;						// ���݂̎��@�Ƃ͕ʂ�2�́@���@�R��

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
