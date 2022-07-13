#include "../../../Object/Enemy.h"
#include "../../Navi/Navi.h"
#include "../../Navi/PatrolNavi.h"
#include "NodeFunc.h"

NodeState MoveFunc::operator()(Obj& obj, float delta)
{
	// �ړ�������
	obj.MovePos(delta);

	// �A�C�h����ԃt���O��false�ɂ���
	obj.SetIdleFlag(false);
	return NodeState::Success;
}

NodeState RotaFunc::operator()(Obj& obj, float delta)
{
	// �G����]������
	dynamic_cast<Enemy&>(obj).Rotation(delta);
	return NodeState::Success;
}


NodeState NaviSetRoutePatrolFunc::operator()(Obj& obj, float delta)
{
	// �i�r���擾
	auto& navi = dynamic_cast<Navi&>(obj.GetComponent(ComponentID::Navi, "Navi"));

	// ����n�_���S�[���Ɍo�H��T������
	navi.Search( obj.GetPos(), dynamic_cast<PatrolNavi&>(obj.GetComponent(ComponentID::PatrolNavi, "Patrol")).GetPos());
	return NodeState::Success;
}

NodeState NaviMoveFunc::operator()(Obj& obj, float delta)
{
	// �i�r���擾
	auto& navi = dynamic_cast<Navi&>(obj.GetComponent(ComponentID::Navi, "Navi"));

	// �x�N�g���Ɛ��K�������x�N�g����p��
	const auto&& moveVec = navi.GetNaviPos() - obj.GetPos();
	auto moveVecN = moveVec.Normalized();
	
	// �������r
	if (moveVec.SqMagnitude() < Math::Square(obj.GetSpeed() * obj.GeSpMag()))
	{
		// �ʏ�̈ړ��x�N�g���̕��������Ƃ����̂܂܃i�r�̎w���̍��W��
		obj.SetPos(navi.GetNaviPos());
		return NodeState::Success;
	}
	
	// �ړ��x�N�g�����Z�b�g
	obj.SetMoveVec(moveVecN);

	// �ړ�����
	obj.SetPos(obj.GetPos() + (moveVecN * obj.GetSpeed() * obj.GeSpMag()));

	// �A�C�h����ԃt���O��false�ɂ���
	obj.SetIdleFlag(false);

	return NodeState::Success;
}

NodeState PatrolMoveFunc::operator()(Obj& obj, float delta)
{
	// ����p�̃i�r���擾
	auto& navi = dynamic_cast<PatrolNavi&>(obj.GetComponent(ComponentID::PatrolNavi, "Patrol"));

	// �x�N�g���Ɛ��K���������̂�p��
	const auto&& moveVec = navi.GetMovePos() - obj.GetPos();
	auto moveVecN = moveVec.Normalized();

	// �������r
	if (moveVec.SqMagnitude() < Math::Square(obj.GetSpeed() * obj.GeSpMag()))
	{
		// �ʏ�̈ړ��x�N�g���̕��������Ƃ����̂܂܃i�r�̎w���̍��W��
		obj.SetPos(navi.GetMovePos());
		return NodeState::Success;
	}

	// �ړ��x�N�g�����Z�b�g
	obj.SetMoveVec(moveVecN);

	// �ړ�����
	obj.SetPos(obj.GetPos() + (moveVecN * obj.GetSpeed() * obj.GeSpMag()));

	// �A�C�h����ԃt���O��false�ɂ���
	obj.SetIdleFlag(false);
	return NodeState::Success;
}

NodeState NaviWaitSearchFunc::operator()(Obj& obj, float delta)
{
	// �i�r���擾
	auto& navi = dynamic_cast<Navi&>(obj.GetComponent(ComponentID::Navi, "Navi"));

	// ��Ԃ��`�F�b�N
	if (navi.GetNaviState() != NaviState::Search)
	{
		// search�ȊO�̎�����
		return NodeState::Success;
	}
	// search���Ȃ̂ŏ�����
	return NodeState::Now;
}


NodeState PatrolNaviStartFunc::operator()(Obj& obj, float delta)
{
	// ����p�i�r���擾
	auto patrol = dynamic_cast<PatrolNavi*>(&obj.GetComponent(ComponentID::PatrolNavi, "Patrol"));
	if (patrol == nullptr)
	{
		return NodeState::Faild;
	}

	// ������J�n����
	patrol->Start();
	return NodeState::Success;
}

NodeState PatrolNaviStopFunc::operator()(Obj& obj, float delta)
{
	// ����p�i�r���擾
	auto patrol = dynamic_cast<PatrolNavi*>(&obj.GetComponent(ComponentID::PatrolNavi, "Patrol"));
	if (patrol == nullptr)
	{
		return NodeState::Faild;
	}
	// ������~����
	patrol->Stop();
	return NodeState::Success;
}

NodeState AnimCorrectMoveVecToAnim::operator()(Obj& obj, float delta)
{
	auto enemy = dynamic_cast<Enemy*>(&obj);
	if (enemy == nullptr)
	{
		return NodeState::Faild;
	}
	// �A�j���[�V������␳����
	enemy->CorrectMoveVecToAnim();
	return NodeState::Success;
}



NodeState EnemyRandRotaFunc::operator()(Obj& obj, float delta)
{
	auto enemy = dynamic_cast<Enemy*>(&obj);
	if (enemy == nullptr)
	{
		return NodeState::Faild;
	}
	enemy->SetRotationAngle();
	return NodeState::Success;
}



EnemyStateTimeWait::EnemyStateTimeWait(float inWaitTime) :
	waitTime_{inWaitTime}
{
}

NodeState EnemyStateTimeWait::operator()(Obj& obj, float delta)
{
	// �G���擾
	auto enemy = dynamic_cast<Enemy*>(&obj);
	if (enemy == nullptr)
	{
		return NodeState::Faild;
	}

	// ���Ԃ��`�F�b�N����
	if (enemy->GetStateTime() > waitTime_)
	{
		// �ҋ@���Ԃ��z���Ă����琬��
		return NodeState::Success;
	}
	// �A�C�h����Ԃɂ���
	obj.SetIdleFlag(true);

	// ���Ԃ��z���ĂȂ��̂ŏ�����
	return NodeState::Now;
}

EnemyStateSetFunc::EnemyStateSetFunc(EnemyState state) :
	state_{state}
{
}

NodeState EnemyStateSetFunc::operator()(Obj& obj, float delta)
{
	auto enemy = dynamic_cast<Enemy*>(&obj);
	if (enemy == nullptr)
	{
		return NodeState::Faild;
	}
	// �G�̏�Ԃ��Z�b�g����
	enemy->SetState(state_);
	return NodeState::Success;
}
