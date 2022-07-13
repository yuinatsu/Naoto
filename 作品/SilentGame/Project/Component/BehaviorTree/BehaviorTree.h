#pragma once
#include <memory>
#include "../Component.h"

class BehaviorBaseNode;

// �r�w�C�r�A�x�[�XAI���m�[�h���g�����c���[�\���Ŏ��N���X
class BehaviorTree :
	public Component
{
public:
	BehaviorTree(std::unique_ptr<BehaviorBaseNode> node,const std::string& name, Obj& owner);
	~BehaviorTree();
private:
	void Update(float delta) override;

	// ��ԏ�ɂ���m�[�h(�J�n�m�[�h)
	std::unique_ptr<BehaviorBaseNode> rootNode_;

	ComponentID GetID() const override;
};

