#pragma once
#include <vector>
#include "../../common/Math.h"
#include "../Component.h"


class TmxObj;

// ����p�N���X
class PatrolNavi : 
	public Component
{
	using Vector2lVec = std::vector<Math::Vector2I>;
	using Vector2lVecItr = Vector2lVec::iterator;
public:
	PatrolNavi(Vector2lVec& route,std::shared_ptr<TmxObj>& tmxObj, const std::string& name, Obj& owner);

	/// <summary> ���s���ׂ����W���擾���� </summary>
	/// <param name=""></param>
	/// <returns> ���W </returns>
	const Math::Vector2 GetMovePos(void) const;

	/// <summary> ���݂̃}�X�� </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const Math::Vector2I& GetPos(void)const;

	/// <summary> ��~���Ă��邩 </summary>
	/// <param name=""></param>
	/// <returns> ��~���Ă���Ƃ�true���Ă��Ȃ��Ƃ�false </returns>
	bool IsStop(void) const;

	/// <summary> ��~������ </summary>
	/// <param name=""></param>
	void Stop(void);

	/// <summary> ������J�n���� </summary>
	/// <param name=""></param>
	void Start(void);

private:

	void Update(float delta) override;

	ComponentID GetID() const;

	// �}�b�v���
	std::shared_ptr<TmxObj> tmxObj_;

	// ����p���[�g
	Vector2lVec patrolRoute_;

	// ����̃}�X��
	Vector2lVecItr patrolPos_;

	// ��~�t���O
	bool stopFlag_;
};

