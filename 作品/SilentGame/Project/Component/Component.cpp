#include "Component.h"

Component::Component(const std::string& name,Obj& owner) :
	owner_{owner}, name_{name}
{
}

Component::~Component()
{
}

// �X�V����
void Component::Update(float delta)
{
	// �������Ȃ�
}

// ���O���擾����
std::string_view Component::GetName(void) const
{
	// ���g�̖��O��Ԃ�
	return name_;
}
