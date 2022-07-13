#include "Collider.h"


Collider::Collider(const GetHitFunc& getHitFunc, const std::string& name, Obj& owner) :
    getHitFunc_{getHitFunc}, Component{ name,owner}, hitFlag_{false}
{
}

Collider::~Collider()
{
}

// ID‚ðŽæ“¾‚·‚é
ComponentID Collider::GetID() const
{
    // ID‚ð•Ô‚·
    return ComponentID::Collider;
}


