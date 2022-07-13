#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include <list>
#include <mutex>
#include <thread>

#include "../../common/Math.h"
#include "../Component.h"

//class DijkstraNode;
//using DijkstraNodeData = std::vector < std::vector<std::shared_ptr<DijkstraNode>>>;

// A*�p�m�[�h
class AstarNode;

// A*�p�m�[�h�̃f�[�^�p
using AstarNodeData = std::vector < std::vector<std::shared_ptr<AstarNode>>>;


class TmxObj;

enum class NaviState
{
	Search,		// �T����
	Find,		// �ړI�n�����݂���Ƃ�
	Non,		// �������Ȃ��~�܂��Ƃ�
};

// �o�H�T���p�N���X
class Navi :
	public Component
{
	using Vector2lVec = std::list<Math::Vector2I>;
	using Vector2lVecItr = Vector2lVec::iterator;
public:
	Navi(std::shared_ptr<TmxObj>& tmxObj,const std::string& name, Obj& owner);
	~Navi();

	/// <summary> �X�^�[�g����S�[���܂ł̌o�H�̒T�� </summary>
	/// <param name="start"> �X�^�[�g�n�_�̍��W </param>
	/// <param name="goal"> �S�[���n�_�̏��� </param>
	void Search(const Math::Vector2& start, const Math::Vector2I& goal);

	void Search(const Math::Vector2& start, const Math::Vector2& goal);

	/// <summary> Navi�N���X�̏�Ԃ��擾���� </summary>
	/// <param name=""></param>
	/// <returns> Navi�N���X�̏�� </returns>
	NaviState GetNaviState(void);

	bool SetNaviState(NaviState state);

	// ���ʂ̎擾(�f�o�b�O�p)
	std::list<Math::Vector2I>& GetResult();

	// ���s���ׂ����W
	const Math::Vector2 GetNaviPos(void);
private:

	void Update(float delta) override;

	/// <summary> �m�[�h�̍쐬 </summary>
	/// <param name="tmxObj"></param>
	//void CreateNode(void);

	
	/// <summary> A*�T���p�̃m�[�h���쐬 </summary>
	/// <param name=""></param>
	void CreateAstarNode(void);

	// void DijkstraSearch(const Math::Vector2I& start, const Math::Vector2I& goal);

	/// <summary> A*�@���g���Čo�H�T�����s�� </summary>
	/// <param name="start"> �J�n�}�X�� </param>
	/// <param name="goal"> �ړI�̃}�X�� </param>
	void AstarSearch(const Math::Vector2I& start, const Math::Vector2I& goal);

	ComponentID GetID() const override;

	// ���݂̖ړI�n�̃}�X��
	Vector2lVecItr nowNaviPos_;


	// �T������
	Vector2lVec destRoute_;

	// �m�[�h(Astar�p�m�[�h)
	AstarNodeData astarNodeData_;

	// �}�b�v�Ɋւ���Tmx�I�u�W�F�N�g
	std::shared_ptr<TmxObj> tmxObj_;

	// �T����Ƃ��s���X���b�h
	std::thread workThread_;

	// �~���[�e�b�N�X
	std::mutex mutex_;

	// ���
	NaviState state_;
};

