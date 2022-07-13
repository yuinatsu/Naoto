#include <DxLib.h>
#include "../../common/ImageMng.h"
#include "../../common/AnimMng.h"
#include "../../common/Debug.h"
#include "../../Component/Collider/CircleCollider.h"
#include "LaundMine.h"

constexpr char laundMineAnim[]{ "./Resource/Image/bomb_black.png" };

LaundMine::LaundMine(const Vector2& pos, EnemyList& enemyList, std::unique_ptr<Obj>& player):
	enemyList_{enemyList_},player_{player}
{
	pos_ = pos;

	AddComponent(std::make_unique<Animation>("DefeatItem", laundMineAnim, *this));
	auto& anim = dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, laundMineAnim));
	lpAnimMng.SetXml("DefeatItem", "Resource/Xml/DefeatItemAnim.xml");
	const std::array<std::string, 2> stateList{ "LaundMine","Exprotion"};
	for (auto& stat : stateList)
	{
		lpAnimMng.SetItem("DefeatItem", stat);
	}
	anim.state("LaundMine");

	AddComponent(std::make_unique<CircleCollider>(
		10.0f,
		[this](Collider& other) {
			if (other.GetOwner().GetObjID() == ObjID::Enemy)
			{
				DebugLog("“–‚½‚Á‚Ä‚¢‚é‚æ");
				other.GetOwner().Destroy();
				alive_ = false;
			}
		},
		"BodyCol",
			* this)
	);

	Init();
}

LaundMine::~LaundMine()
{

}

void LaundMine::Init(void)
{

}

void LaundMine::Update(double delta)
{
}

void LaundMine::Draw(const Math::Vector2& drawffset)
{
	if (alive_ == true)
	{
		dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, laundMineAnim)).Draw(pos_ + drawffset, Math::zeroVector2<float>, true);
		//(GetComponent(ComponentID::Collider, "BodyCol")).DbgDraw(pos_ + drawffset);
	}
}
