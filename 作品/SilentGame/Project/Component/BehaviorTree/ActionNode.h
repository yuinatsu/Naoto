#pragma once
#include <functional>
#include "BehaviorBaseNode.h"

using ActFunc = std::function<NodeState(Obj&, float)>;

// �A�N�V�����m�[�h(���[�ŉ��������s����)
class ActionNode :
	public BehaviorBaseNode
{
public:
	ActionNode(const ActFunc& actFunc);
	~ActionNode();
private:
	// ���s����֐�
	ActFunc actFunc_;

	NodeState operator()(Obj& obj, float delta) override;
	std::unique_ptr<BehaviorBaseNode> Copy(void) override;
};

