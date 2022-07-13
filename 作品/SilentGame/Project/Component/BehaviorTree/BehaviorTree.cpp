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
	// �X�V���ʂ��`�F�b�N����
	if ((*rootNode_)(owner_, delta) != NodeState::Now)
	{
		// ���s���ł͂Ȃ��Ƃ����Z�b�g��������
		rootNode_->Reset();
	}
}

ComponentID BehaviorTree::GetID() const
{
	return ComponentID::BehaviorTree;
}
