#include "../Component/Collider/CircleCollider.h"
#include "../Component/Animation.h"
#include "../common/AnimMng.h"

#include "Decoy.h"

Decoy::Decoy(const Math::Vector2& pos)
{
	pos_ = pos;
	AddComponent(
		std::make_unique<CircleCollider>(
			15.0f,
			[this](Collider& other) {
				/*if (obj.GetObjID() != ObjID::Player)
				{
					alive_ = false;
				}*/
			},
			"BodyCol",
			*this
			));
	lpAnimMng.SetXml("Item", "Resource/Xml/ItemImage.tsx");
	lpAnimMng.SetItem("Item", "Decoy");
	AddComponent(std::make_unique<Animation>("Item", "Anim", *this));
	dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, "Anim")).state("Decoy");

}

Decoy::~Decoy()
{
}

bool Decoy::Init(void)
{
	return false;
}

void Decoy::Update(double delta)
{
	UpdateComponent(delta);
}

void Decoy::Draw(const Math::Vector2& offset)
{
	dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, "Anim")).Draw(pos_ + offset,Math::zeroVector2<float>, true);
	//(GetComponent(ComponentID::Collider, "BodyCol")).DbgDraw(offset);
}
