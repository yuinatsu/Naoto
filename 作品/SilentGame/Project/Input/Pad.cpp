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
	// keyList_�Ƀ{�^���z�u���Z�b�g
	keyList_.try_emplace(InputID::Up, XINPUT_BUTTON_DPAD_UP);					// ��
	keyList_.try_emplace(InputID::Down, XINPUT_BUTTON_DPAD_DOWN);				// ��
	keyList_.try_emplace(InputID::Left, XINPUT_BUTTON_DPAD_LEFT);				// ��
	keyList_.try_emplace(InputID::Right, XINPUT_BUTTON_DPAD_RIGHT);				// �E
	keyList_.try_emplace(InputID::Dash, XINPUT_BUTTON_LEFT_SHOULDER);			// LB
	keyList_.try_emplace(InputID::Crouch, XINPUT_BUTTON_RIGHT_SHOULDER);		// RB
	keyList_.try_emplace(InputID::ItemLeft, 0);									// LT
	keyList_.try_emplace(InputID::ItemRight, 0);								// RT
	keyList_.try_emplace(InputID::Attack, XINPUT_BUTTON_B);						// B�{�^��
	keyList_.try_emplace(InputID::btn1, XINPUT_BUTTON_A);						// A�{�^��

	for (auto id : InputID())
	{
		cntData_.try_emplace(id, TrgBool{ 0, 0 });			// ���͏�񏉊���
	}
	padID_ = padCnt_++;
	return true;
}

void Pad::Update(double delta)
{
	GetJoypadXInputState(padID_, &input_);					// �{�^���f�[�^���܂Ƃ߂Ď擾
	// �{�^���̍X�V
	for (auto id : InputID())
	{
		cntData_[id][static_cast<int>(Trg::Old)] = cntData_[id][static_cast<int>(Trg::Now)];
		cntData_[id][static_cast<int>(Trg::Now)] = input_.Buttons[keyList_[id]];
	}
	// �X�e�B�b�N�̍X�V
	StickUpdate();
}

void Pad::StickUpdate(void)
{
	//// ���X�e�B�b�N��X��
	//if (input_.ThumbLX > motionRange)
	//{
	//	// �E����
	//	cntData_[InputID::Right][static_cast<int>(Trg::Now)] = 1;
	//}
	//else if (input_.ThumbLX < -motionRange)
	//{
	//	// ������
	//	cntData_[InputID::Left][static_cast<int>(Trg::Now)] = 1;
	//}
	//else
	//{
	//	// ���͂Ȃ�
	//	cntData_[InputID::Left][static_cast<int>(Trg::Now)] = 0;
	//	cntData_[InputID::Right][static_cast<int>(Trg::Now)] = 0;
	//}
	//// ���X�e�B�b�N��Y��
	//if (input_.ThumbLY > motionRange)
	//{
	//	// �����
	//	cntData_[InputID::Up][static_cast<int>(Trg::Now)] = 1;
	//}
	//else if (input_.ThumbLY < -motionRange)
	//{
	//	// ������
	//	cntData_[InputID::Down][static_cast<int>(Trg::Now)] = 1;
	//}
	//else
	//{
	//	// ���͂Ȃ�
	//	cntData_[InputID::Down][static_cast<int>(Trg::Now)] = 0;
	//	cntData_[InputID::Up][static_cast<int>(Trg::Now)] = 0;
	//}

	// �E�X�e�B�b�N��X��
	if (input_.ThumbRX > motionRange)
	{
		// �E����
		cntData_[InputID::ItemRight][static_cast<int>(Trg::Now)] = 1;
	}
	else if (input_.ThumbRX < -motionRange)
	{
		// ������
		cntData_[InputID::ItemLeft][static_cast<int>(Trg::Now)] = 1;
	}
	else
	{
		// ���͂Ȃ�
		cntData_[InputID::ItemLeft][static_cast<int>(Trg::Now)] = 0;
		cntData_[InputID::ItemRight][static_cast<int>(Trg::Now)] = 0;
	}
}
