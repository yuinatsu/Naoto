#pragma once
#include <functional>
#include "../Component.h"

class Obj;
class CircleCollider;
class FanCollider;
class Collider;
using GetHitFunc = std::function<void(Collider&)>;


// �����蔻��p�N���X�̊��N���X
class Collider :
	public Component
{
public:

	/// <summary> �R���X�g���N�^ </summary>
	/// <param name="getHitFunc"> �����������̏�����function�� </param>
	/// <param name="owner"> ������ </param>
	Collider(const GetHitFunc& getHitFunc, const std::string& name,Obj& owner);
	virtual ~Collider();

	/// <summary> �Ώۂ̃R���C�_�[�Ɠ������Ă��邩�𒲂ׂ鏈�� </summary>
	/// <param name="col"> �Ώۂ̃R���C�_�[ </param>
	virtual void HitCheck(Collider& col) = 0;

	virtual bool HitBoolCheck(Collider& col) = 0;

	/// <summary> �Ώۂ̃R���C�_�[�Ɠ������Ă��邩�𒲂ׂ鏈��(�����o��������) </summary>
	/// <param name="col">�Ώۂ̃R���C�_�[</param>
	virtual bool HitExCheck(Collider& col) = 0;

	/// <summary> �T�[�N���R���C�_�[�Ƃ̓����蔻��𒲂ׂ� </summary>
	/// <param name="col"> �T�[�N���R���C�_�[ </param>
	/// <returns></returns>
	virtual bool HitCheck(CircleCollider& col) = 0;

	/// <summary> �T�[�N���R���C�_�[�Ƃ̓����蔻��𒲂ׂ�(�����o��) </summary>
	/// <param name="col">�T�[�N���R���C�_�[</param>
	/// <returns></returns>
	virtual bool HitExCheck(CircleCollider& col) = 0;

	virtual bool HitCheck(FanCollider& col) = 0;

	Obj& GetOwner() { return owner_; }
	GetHitFunc& GetFunc(void) { return getHitFunc_; }

	bool IsHit(void)const { return hitFlag_; }
	void Hit(void) { hitFlag_ = true; }
	void HitFlagUpdate(void) { hitFlag_ = false; }
protected:
	bool hitFlag_;

	/// <summary> �����������̏���������function </summary>
	GetHitFunc getHitFunc_;
private:

	/// <summary> ID���擾���� </summary>
	/// <returns> ID </returns>
	ComponentID GetID() const override;
};

