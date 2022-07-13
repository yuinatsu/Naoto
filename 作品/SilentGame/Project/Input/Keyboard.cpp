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
	// keyList_にキー配置をセット
	keyList_.try_emplace(InputID::Up, KEY_INPUT_UP);					// 上キー
	keyList_.try_emplace(InputID::Down, KEY_INPUT_DOWN);				// 下キー
	keyList_.try_emplace(InputID::Left, KEY_INPUT_LEFT);				// 左キー
	keyList_.try_emplace(InputID::Right, KEY_INPUT_RIGHT);				// 右キー
	keyList_.try_emplace(InputID::Dash, KEY_INPUT_LSHIFT);				// 左シフト
	keyList_.try_emplace(InputID::Crouch, KEY_INPUT_LCONTROL);			// 左コントロール
	keyList_.try_emplace(InputID::ItemLeft, KEY_INPUT_X);				// Xキー
	keyList_.try_emplace(InputID::ItemRight, KEY_INPUT_C);				// Cキー
	keyList_.try_emplace(InputID::Attack, KEY_INPUT_Z);					// Xキー
	keyList_.try_emplace(InputID::btn1, KEY_INPUT_ESCAPE);				// Escapeキー
	for (auto id : InputID())
	{
		cntData_[id].fill(false);			// 入力情報初期化
	}
	return true;
}

void Keyboard::Update(double delta)
{
	GetHitKeyStateAll(keyData_.data());		// キーデータをまとめて取得
	// キーデータ更新
	for (auto&& id : InputID())
	{
		cntData_[id][static_cast<int>(Trg::Old)] = cntData_[id][static_cast<int>(Trg::Now)];
		cntData_[id][static_cast<int>(Trg::Now)] = keyData_[keyList_[id]];
	}
}
