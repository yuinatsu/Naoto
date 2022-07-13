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

	// 座標(マス目)
	Math::Vector2I pos_;

	Math::Vector2I beforPos_;

	// 隣接ノード
	std::list<std::shared_ptr<AstarNode>> nextNode_;

	// ヒューリスティックコスト(ゴールまでの距離をコストに)
	float heuristicCost_;

	// 合計コスト
	float totalCost_;

};

