#include <DxLib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Keyboard.h"

Keyboard::Keyboard()
{
	Init();
}

Keyboard::~Keyboard()
{
}

bool Keyboard::Init(void)
{
	// keyList_�ɃL�[�z�u���Z�b�g
	keyList_.try_emplace(InputID::Up, KEY_INPUT_UP);					// ��L�[
	keyList_.try_emplace(InputID::Down, KEY_INPUT_DOWN);				// ���L�[
	keyList_.try_emplace(InputID::Left, KEY_INPUT_LEFT);				// ���L�[
	keyList_.try_emplace(InputID::Right, KEY_INPUT_RIGHT);				// �E�L�[
	keyList_.try_emplace(InputID::Dash, KEY_INPUT_LSHIFT);				// ���V�t�g
	keyList_.try_emplace(InputID::Crouch, KEY_INPUT_LCONTROL);			// ���R���g���[��
	keyList_.try_emplace(InputID::ItemLeft, KEY_INPUT_X);				// X�L�[
	keyList_.try_emplace(InputID::ItemRight, KEY_INPUT_C);				// C�L�[
	keyList_.try_emplace(InputID::Attack, KEY_INPUT_Z);					// X�L�[
	keyList_.try_emplace(InputID::btn1, KEY_INPUT_ESCAPE);				// Escape�L�[
	for (auto id : InputID())
	{
		cntData_[id].fill(false);			// ���͏�񏉊���
	}
	return true;
}

void Keyboard::Update(double delta)
{
	GetHitKeyStateAll(keyData_.data());		// �L�[�f�[�^���܂Ƃ߂Ď擾
	// �L�[�f�[�^�X�V
	for (auto&& id : InputID())
	{
		cntData_[id][static_cast<int>(Trg::Old)] = cntData_[id][static_cast<int>(Trg::Now)];
		cntData_[id][static_cast<int>(Trg::Now)] = keyData_[keyList_[id]];
	}
}
