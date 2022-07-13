#pragma once
#include <string>
#include "../common/Math.h"
#include "ComponentID.h"
class Obj;

/// <summary> �I�u�W�F�N�g�ɋ@�\����������p�̊��N���X </summary>
class Component
{
public:

	/// <summary> �R���X�g���N�^ </summary>
	/// <param name="owner"> ������̃I�u�W�F�N�g </param>
	Component(const std::string& name,Obj& owner);

	/// <summary> �f�X�g���N�^ </summary>
	virtual ~Component();

	/// <summary> �X�V���� </summary>
	/// <param name="delta"> �f���^�^�C�� </param>
	virtual void Update(float delta);

	/// <summary> �R���|�[�l���g�̖��O���擾 </summary>
	/// <param name=""></param>
	/// <returns> �R���|�[�l���g�̖��O </returns>
	std::string_view GetName(void) const;

	virtual ComponentID GetID() const = 0;
#ifdef _DEBUG
	virtual void DbgDraw(const Math::Vector2& offset) const {}
#endif
protected:

	/// <summary> ������ </summary>
	Obj& owner_;

	// ���O
	std::string name_;
};

