#pragma once
#include <memory>
#include "../Component.h"

class BehaviorBaseNode;

// ビヘイビアベースAIをノードを使ったツリー構造で持つクラス
class BehaviorTree :
	public Component
{
public:
	BehaviorTree(std::unique_ptr<BehaviorBaseNode> node,const std::string& name, Obj& owner);
	~BehaviorTree();
private:
	void Update(float delta) override;

	// 一番上にあるノード(開始ノード)
	std::unique_ptr<BehaviorBaseNode> rootNode_;

	ComponentID GetID() const override;
};

