#include "Component.h"

Component::Component(const std::string& name,Obj& owner) :
	owner_{owner}, name_{name}
{
}

Component::~Component()
{
}

// 更新処理
void Component::Update(float delta)
{
	// 何もしない
}

// 名前を取得する
std::string_view Component::GetName(void) const
{
	// 自身の名前を返す
	return name_;
}
