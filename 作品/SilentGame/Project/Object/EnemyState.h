#pragma once

enum class EnemyState
{
	Trace,       // ���E�Ɋւ����Ԃ̎�
	Sound,       // ���ɔ��������Ƃ��̏��
	Gimic,      // �M�~�b�N�ɑ΂��锽�������������̔���
	Patrol,       // ����
	MovePatrol,   // ����n�_�ɖ߂邽�߂Ɉړ�����ړ�����
	Item,		// �W�Q������������̔���
	Non,         // �����Ȃ�
	Lost,		// ������������x�����Ă��鎞�̔���
	Look,		// �������u�Ԃ̏��
};
