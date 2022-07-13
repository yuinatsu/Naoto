#pragma once
#include <memory>
#include "../common/Math.h"
#include "../common/Random.h"
#include "EnemyState.h"
#include "Unit.h"

class Random;
class  CameraMng;
struct Fan;



class TmxObj;

class Enemy :
	public Unit
{
public:
	Enemy(std::vector<Math::Vector2I>& route,std::shared_ptr<TmxObj>& tmxObj, const Math::Vector2& pos);
	~Enemy();

	/// <summary> �G�̏�Ԃ��擾 </summary>
	/// <param name=""></param>
	/// <returns> �G�̏�� </returns>
	EnemyState GetEnemyState(void) const;

	/// <summary> �G�̏�Ԃ��Z�b�g���� </summary>
	/// <param name="state"> �Z�b�g��������� </param>
	void SetState(EnemyState state);

	/// <summary> ��]�p�x��ݒ肷�� </summary>
	/// <param name="angle"> ��]�I���p�x </param>
	void SetRotationAngle(float angle);

	/// <summary> �K���ɉ�]������ </summary>
	/// <param name=""></param>
	void SetRotationAngle(void);

	/// <summary> ��]������ </summary>
	/// <param name="delta"></param>
	void Rotation(double delta);

	/// <summary> �ړ���������A�j���[�V������؂�ւ��� </summary>
	/// <param name=""></param>
	void CorrectMoveVecToAnim(void);

	const float GetStateTime(void) const;
private:
	bool Init(void);
	void Update(double delta) override; 
	void Draw(const Math::Vector2& offset)override;

	ObjID GetObjID(void) override { return ObjID::Enemy; };      // id�̎擾


	// �G�̏��
	EnemyState state_;

	// �U��������x
	const float rotSpeed_ = Math::Deg2Rad(5.0f);

	// �U������p�x
	float targetAngle_ = 0.0f;

	// �U��������E�ǂ��炩
	float angleSing_ = 1.0f;

	// ���݂̃X�e�[�g�ɂȂ��Ă���̌o�ߎ���
	float stateTime_;

	friend struct EnemyCheckAngleFunc;

};

