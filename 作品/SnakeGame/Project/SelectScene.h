#pragma once
#include "SCN_ID.h"
#include "CharImage.h"
#include "Player.h"
#include "Vector2.h"
#include "common.h"

#define CHAR_SEL_IMAGE_SIZE_X 400							// �L�����Z���N�g���S��X���W
#define CHAR_SEL_IMAGE_SIZE_Y 80							// �L�����Z���N�g���S��Y���W

#define CHAR_OPE_IMAGE_SIZE_X 200							// �I�𑀍샍�S��X���W
#define CHAR_OPE_IMAGE_SIZE_Y 40							// �I�𑀍샍�S��Y���W

#define CHAR_OPE_MAX 4										// �I�𑀍샍�S�̍ő吔

class SelectScene
{
public:
	SelectScene();																					// SelestScene�̐���
	~SelectScene();																					// SelestScene�̔j��
	SCN_ID Update(char* keyData, char* keyDataOld);													// SelestScene�̍X�V
	bool SelectChar(Player* player, DIR dir, int count, CHAR_ID limID, CHAR_ID setID);				// �L�����Z���N�g�L�[���͊֐� 			// (�I���v���C���[, �L�[���͕���, ID�̕ω���, ID�̍ő�l, ID�̍ő�l�܂ōs�������̒l)
	bool DesideChar(Player* player, DIR dir, PL_ST state);											// �L��������L�[���͊֐�				// (�I���v���C���[, �L�[���͕���, �v���C���[�̏��)
	void Draw(void);																				// SelestScene�̕`��
	bool Init(void);
	bool Relese(void);

	Vector2 screenSize_;																	// �X�N���[���T�C�Y
	Player player[PLAYER_MAX];																// �v���C���[
	CharImage charImage[static_cast<int>(CHAR_ID::MAX)];									// �I���L�����p�C���[�W
	int logoImage_;																			// �L�����I�𒆂̃��S
	int bgImage_;																			// �Q�[���w�i
private:
};

