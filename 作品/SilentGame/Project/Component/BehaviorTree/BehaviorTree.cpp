#include "BehaviorBaseNode.h"
#include "BehaviorTree.h"

BehaviorTree::BehaviorTree(std::unique_ptr<BehaviorBaseNode> node, const std::string& name, Obj& owner) :
	Component{name,owner} , rootNode_{std::move(node)}
{
	rootNode_->Reset();
}

BehaviorTree::~BehaviorTree()
{
}

void BehaviorTree::Update(float delta)
{
	// 更新結果をチェックする
	if ((*rootNode_)(owner_, delta) != NodeState::Now)
	{
		// 実行中ではないときリセットをかける
		rootNode_->Reset();
	}
}

ComponentID BehaviorTree::GetID() const
{
	return ComponentID::BehaviorTree;
}
