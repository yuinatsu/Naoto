#include "../Component/Collider/CircleCollider.h"
#include "../Component/Animation.h"
#include "../common/AnimMng.h"
#include "Enemy.h"
#include "Alcohol.h"

Alcohol::Alcohol(const Math::Vector2& pos)
{
    pos_ = pos;
	AddComponent(
		std::make_unique<CircleCollider>(
			15.0f,
			[this](Collider& other) {
			},
			"BodyCol",
				*this
				));
	lpAnimMng.SetXml("Item", "Resource/Xml/ItemImage.tsx");
	lpAnimMng.SetItem("Item", "Alcohol");
	AddComponent(std::make_unique<Animation>("Item", "Anim", *this));
	dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, "Anim")).state("Alcohol");

}

Alcohol::~Alcohol()
{
}

bool Alcohol::Init(void)
{
    return false;
}

void Alcohol::Update(double delta)
{
	UpdateComponent(delta);
}

void Alcohol::Draw(const Math::Vector2& offset)
{
	dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, "Anim")).Draw(pos_ + offset, Math::zeroVector2<float>, true);
	//(GetComponent(ComponentID::Collider, "BodyCol")).DbgDraw(offset);
}
