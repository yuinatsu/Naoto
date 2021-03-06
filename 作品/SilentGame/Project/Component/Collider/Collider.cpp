#include "Collider.h"


Collider::Collider(const GetHitFunc& getHitFunc, const std::string& name, Obj& owner) :
    getHitFunc_{getHitFunc}, Component{ name,owner}, hitFlag_{false}
{
}

Collider::~Collider()
{
}

// IDを取得する
ComponentID Collider::GetID() const
{
    // IDを返す
    return ComponentID::Collider;
}


