#pragma once
#include <memory>
#include <list>
#include "../../common/Math.h"

class AstarNode
{
public:
	AstarNode(const Math::Vector2I& pos);
	void PushNextNode(std::shared_ptr<AstarNode>& node);
	void Clear();

	const float GetTotalCost(void) const;
	void SetTotalCost(float cost);

	const float GetHeuristicCost(void) const;
	void CalculateHeuristicCost(const Math::Vector2I& pos);

	const std::list<std::shared_ptr<AstarNode>>& GetNextNode(void) const { return nextNode_; };

	const Math::Vector2I& GetPos(void) const;

private:

	// ���W(�}�X��)
	Math::Vector2I pos_;

	Math::Vector2I beforPos_;

	// �אڃm�[�h
	std::list<std::shared_ptr<AstarNode>> nextNode_;

	// �q���[���X�e�B�b�N�R�X�g(�S�[���܂ł̋������R�X�g��)
	float heuristicCost_;

	// ���v�R�X�g
	float totalCost_;

};

