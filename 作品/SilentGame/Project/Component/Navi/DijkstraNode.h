#pragma once
#include <memory>
#include <list>
#include "../../common/Math.h"

// �_�C�N�X�g���@�Ŏg���m�[�h
class DijkstraNode
{
public:
	DijkstraNode(const Math::Vector2I& pos);
	~DijkstraNode();

	/// <summary> �g�[�^���R�X�g���Z�b�g�� </summary>
	/// <param name="cost"> �g�[�^���R�X�g </param>
	void SetTotalCost(const int cost);

	/// <summary> �g�[�^���R�X�g���擾���� </summary>
	/// <param name=""></param>
	/// <returns> �g�[�^���R�X�g </returns>
	const int GetTotalCost(void) const;

	/// <summary> �T�����I�������m�[�h���H </summary>
	/// <param name=""></param>
	/// <returns> �I����true�I�����Ă��Ȃ��Ƃ�false </returns>
	bool IsEnd(void) const;

	/// <summary> �I�������� </summary>
	/// <param name=""></param>
	void End(void);

	/// <summary> �ړ����̃m�[�h�̏��ڂ��Z�b�g���� </summary>
	/// <param name="befor"></param>
	void SetBeforPos(const Math::Vector2I& befor);

	/// <summary> �ړ����̃m�[�h�̏��ڂ��擾���� </summary>
	/// <param name=""></param>
	/// <returns> �ړ����̃m�[�h�̏��� </returns>
	const Math::Vector2I& GetBeforPos(void) const;

	/// <summary> �T���J�n�O�ɃR�X�g�������������� </summary>
	/// <param name=""></param>
	void Clear(void);

	/// <summary> �m�[�h�̏��ڂ��擾���� </summary>
	/// <param name=""></param>
	/// <returns> ���̃m�[�h�̏��� </returns>
	const Math::Vector2I GetPos(void) const;

	/// <summary> �אڃm�[�h��ǉ����� </summary>
	/// <param name="node"> �ǉ�����m�[�h </param>
	void PushNextNode(std::shared_ptr<DijkstraNode>& node);

	/// <summary> �_�C�N�X�g���@�ɂ��אڃm�[�h�̃R�X�g���X�V���� </summary>
	/// <param name=""></param>
	void CheckNextNode(void);
private:

	// �אڃm�[�h
	std::list<std::shared_ptr< DijkstraNode>> nextNode_;

	// �m�[�h�̏���
	Math::Vector2I pos_;

	// �ړ����m�[�h�̏���
	Math::Vector2I beforPos_;

	// �I���t���O
	bool endFlag_;

	// �g�[�^���R�X�g
	int totalCost_;
};

