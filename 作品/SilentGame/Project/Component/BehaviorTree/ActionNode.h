#pragma once
#include <functional>
#include "BehaviorBaseNode.h"

using ActFunc = std::function<NodeState(Obj&, float)>;

// アクションノード(末端で何かを実行する)
class ActionNode :
	public BehaviorBaseNode
{
public:
	ActionNode(const ActFunc& actFunc);
	~ActionNode();
private:
	// 実行する関数
	ActFunc actFunc_;

	NodeState operator()(Obj& obj, float delta) override;
	std::unique_ptr<BehaviorBaseNode> Copy(void) override;
};

