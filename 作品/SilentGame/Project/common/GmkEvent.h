#pragma once
#include <list>
#include <memory>
#include <functional>
#include <unordered_map>
#include "Math.h"

class Obj;

enum class EventType
{
	Alert,		// �Ď��J�����Ƃ��Ɍ����������ɃT�C�������Ȃ�^�C�v
	Enemy,				// �G�Ɍ���������
	Non,		// ���ɉ����N���Ă��Ȃ��Ƃ�
};


class GmkEvent
{
	using GmkFuncMap = std::unordered_map < EventType, std::pair<std::function<void(float)>, std::function<void(void)>>>;
public:
	GmkEvent();
	~GmkEvent();
	// �v���C���[�𔭌��������̃C�x���g
	void DisPlayer(bool flag,float delta);

	void StartEvent(std::list<std::unique_ptr<Obj>>& enemyList, const Math::Vector2& pos,EventType type);

	void Update(float delta);
	void Draw(void);

private:

	// �A���[�g�̍X�V�ƕ`��
	void AlertUpdate(float delta);
	void AlertDraw(void);

	// �M�~�b�N�C�x���g���Ƃ̍X�V�ƕ`�揈����state�Ő؂�ւ���p��
	GmkFuncMap gmkFunc_;

	// �o�ߎ���
	float gmkStepTime_;

	// ���݂̃C�x���g�̎��
	EventType nowType_;

	// �v���C���[�������ĉ��b�������̂�
	float Time_;
	// �������̕`��P�x�̒���
	bool flag_;
	float sColor_;
	bool scFlag_;
	// �v���C���[�������������̍��W������
	Math::Vector2 sPos_;

};

