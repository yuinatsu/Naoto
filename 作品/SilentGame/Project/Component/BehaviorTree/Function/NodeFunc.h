#pragma once
#include "../NodeState.h"

class Obj;

// �ړ�
struct MoveFunc
{
	NodeState operator()(Obj& obj, float delta);
};

// ��]
struct RotaFunc
{
	NodeState operator()(Obj& obj, float delta);
};

// �G����]������
struct EnemyRandRotaFunc
{
	NodeState operator()(Obj& obj, float delta);
};



// Navi�̖ړI�n������n�_�ɂ���
struct NaviSetRoutePatrolFunc
{
	NodeState operator()(Obj& obj, float delta);
};

// Navi�ɏ]��Obj���ړ�������
struct NaviMoveFunc
{
	NodeState operator()(Obj& obj, float delta);
};

// PatrolNavi�ɏ]��Obj���ړ�������
struct PatrolMoveFunc
{
	NodeState operator()(Obj& obj, float delta);
};

// Navi�̒T����ҋ@����
struct NaviWaitSearchFunc
{
	NodeState operator()(Obj& obj, float delta);
};

// ������J�n����
struct PatrolNaviStartFunc
{
	NodeState operator()(Obj& obj, float delta);
};

// ������~����
struct PatrolNaviStopFunc
{
	NodeState operator()(Obj& obj, float delta);
};

// MoveVec�����ƂɃA�j���[�V�������Z�b�g����
struct AnimCorrectMoveVecToAnim
{
	NodeState operator()(Obj& obj, float delta);
};


// �G�̏�Ԏ��Ԃ��w�莞�ԂɂȂ�܂ő҂���
struct EnemyStateTimeWait
{
	EnemyStateTimeWait(float inMaxTime);
	NodeState operator()(Obj& obj, float delta);
private:
	const float waitTime_;
};

// �G�̏�Ԃ��Z�b�g���鏈��
struct EnemyStateSetFunc
{
	EnemyStateSetFunc(EnemyState state);
	NodeState operator()(Obj& obj, float delta);
private:
	const EnemyState state_;

};