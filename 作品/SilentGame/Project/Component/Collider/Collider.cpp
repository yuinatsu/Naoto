#include "Collider.h"


Collider::Collider(const GetHitFunc& getHitFunc, const std::string& name, Obj& owner) :
    getHitFunc_{getHitFunc}, Component{ name,owner}, hitFlag_{false}
{
}

Collider::~Collider()
{
}

// ID���擾����
ComponentID Collider::GetID() const
{
    // ID��Ԃ�
    return ComponentID::Collider;
}


