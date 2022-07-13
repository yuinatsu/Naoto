#include "Pad.h"

Pad::Pad()
{
	padCnt_ = 1;
	Init();
}

Pad::~Pad()
{
}

bool Pad::Init(void)
{
	// keyList_にボタン配置をセット
	keyList_.try_emplace(InputID::Up, XINPUT_BUTTON_DPAD_UP);					// 上
	keyList_.try_emplace(InputID::Down, XINPUT_BUTTON_DPAD_DOWN);				// 下
	keyList_.try_emplace(InputID::Left, XINPUT_BUTTON_DPAD_LEFT);				// 左
	keyList_.try_emplace(InputID::Right, XINPUT_BUTTON_DPAD_RIGHT);				// 右
	keyList_.try_emplace(InputID::Dash, XINPUT_BUTTON_LEFT_SHOULDER);			// LB
	keyList_.try_emplace(InputID::Crouch, XINPUT_BUTTON_RIGHT_SHOULDER);		// RB
	keyList_.try_emplace(InputID::ItemLeft, 0);									// LT
	keyList_.try_emplace(InputID::ItemRight, 0);								// RT
	keyList_.try_emplace(InputID::Attack, XINPUT_BUTTON_B);						// Bボタン
	keyList_.try_emplace(InputID::btn1, XINPUT_BUTTON_A);						// Aボタン

	for (auto id : InputID())
	{
		cntData_.try_emplace(id, TrgBool{ 0, 0 });			// 入力情報初期化
	}
	padID_ = padCnt_++;
	return true;
}

void Pad::Update(double delta)
{
	GetJoypadXInputState(padID_, &input_);					// ボタンデータをまとめて取得
	// ボタンの更新
	for (auto id : InputID())
	{
		cntData_[id][static_cast<int>(Trg::Old)] = cntData_[id][static_cast<int>(Trg::Now)];
		cntData_[id][static_cast<int>(Trg::Now)] = input_.Buttons[keyList_[id]];
	}
	// スティックの更新
	StickUpdate();
}

void Pad::StickUpdate(void)
{
	//// 左スティックのX軸
	//if (input_.ThumbLX > motionRange)
	//{
	//	// 右入力
	//	cntData_[InputID::Right][static_cast<int>(Trg::Now)] = 1;
	//}
	//else if (input_.ThumbLX < -motionRange)
	//{
	//	// 左入力
	//	cntData_[InputID::Left][static_cast<int>(Trg::Now)] = 1;
	//}
	//else
	//{
	//	// 入力なし
	//	cntData_[InputID::Left][static_cast<int>(Trg::Now)] = 0;
	//	cntData_[InputID::Right][static_cast<int>(Trg::Now)] = 0;
	//}
	//// 左スティックのY軸
	//if (input_.ThumbLY > motionRange)
	//{
	//	// 上入力
	//	cntData_[InputID::Up][static_cast<int>(Trg::Now)] = 1;
	//}
	//else if (input_.ThumbLY < -motionRange)
	//{
	//	// 下入力
	//	cntData_[InputID::Down][static_cast<int>(Trg::Now)] = 1;
	//}
	//else
	//{
	//	// 入力なし
	//	cntData_[InputID::Down][static_cast<int>(Trg::Now)] = 0;
	//	cntData_[InputID::Up][static_cast<int>(Trg::Now)] = 0;
	//}

	// 右スティックのX軸
	if (input_.ThumbRX > motionRange)
	{
		// 右入力
		cntData_[InputID::ItemRight][static_cast<int>(Trg::Now)] = 1;
	}
	else if (input_.ThumbRX < -motionRange)
	{
		// 左入力
		cntData_[InputID::ItemLeft][static_cast<int>(Trg::Now)] = 1;
	}
	else
	{
		// 入力なし
		cntData_[InputID::ItemLeft][static_cast<int>(Trg::Now)] = 0;
		cntData_[InputID::ItemRight][static_cast<int>(Trg::Now)] = 0;
	}
}
