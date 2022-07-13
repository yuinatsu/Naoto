#include <algorithm>
#include "../Component/Component.h"
#include "Obj.h"
#include "../common/Debug.h"

#include "../common/MapCollMng.h"

Obj::Obj() :
    alive_{true}
{
}

Obj::~Obj()
{
}

void Obj::Update(double delta)
{
    //delta_ = delta;
    UpdateComponent(delta);
}

//void Obj::Draw(void) const
//{
//}

void Obj::Draw(const Math::Vector2& offset)
{
}

const std::unordered_map<std::string_view, ComponentUPTr>& Obj::GetComponent(ComponentID id) const
{
    if (!componentList_.contains(id))
    {
        return (componentList_.begin()->second);
    }
    return componentList_.at(id);

}



Component& Obj::GetComponent(ComponentID id, std::string_view name) const
{
    if (!componentList_.contains(id))
    {
        return (*componentList_.begin()->second.begin()->second);
    }
    if (!componentList_.at(id).contains(name))
    {
        return (*componentList_.at(id).begin()->second);
    }
    return *componentList_.at(id).at(name);
}

bool Obj::IncludeComponent(ComponentID id) const
{
    return componentList_.contains(id);
}

bool Obj::IncludeComponent(ComponentID id, std::string_view name) const
{
    if (componentList_.contains(id))
    {
        return componentList_.at(id).contains(name);
    }
    return false;
}

bool Obj::AddComponent(ComponentUPTr&& component)
{
    auto result = componentList_[component->GetID()].try_emplace(component->GetName(),std::move(component));
    return result.second;
}

bool Obj::RemoveComponent(ComponentID id,std::string_view name)
{
    // キーが存在するかチェック
    if (!componentList_.contains(id))
    {
        // 存在しないとき失敗
        return false;
    }

    if (!componentList_[id].contains(name))
    {
        return false;
    }
    // 存在するとき対象のコンポーネントを削除
    componentList_[id].erase(name);
    return true;
}

const Math::Vector2& Obj::GetPos(void) const
{
    return pos_;
}

void Obj::SetPos(const Math::Vector2& pos)
{
    pos_ = pos;
}

void Obj::SetMoveVec(const Math::Vector2& moveVec)
{
    moveVec_ = moveVec ;
}

const Math::Vector2& Obj::GetMoveVec(void) const
{
    return moveVec_;
}

void Obj::MovePos(double delta)
{
    MapCollMng::Ray ray{ pos_,moveVec_ * speed_ * spMag_ };
    for (auto& c : tmx_->GetColList())
    {
        const auto& [flag, moveV, colV] = MapCollMng::CheckColl2(ray, c);
        if (flag)
        {
            if (Math::Dot(moveVec_, colV) > 0.0f)
            {
                auto val = 1.0f - (moveV.SqMagnitude() / Math::Square(speed_ * spMag_));
                moveVec_ = (moveV + (colV * val)).Normalized();
            }
            else
            {
                auto val = 1.0f - (moveV.SqMagnitude() / Math::Square(speed_ * spMag_));
                moveVec_ = (moveV + (-colV * val)).Normalized();
            }
            break;
        }
    }

    // 後でデルタタイム使ったものに変更予定
    pos_ += moveVec_ * speed_ * spMag_;
}

bool Obj::IsMove(void)
{
    MapCollMng::Ray ray{ pos_,moveVec_ * speed_ * spMag_ };
    for (auto& c : tmx_->GetColList())
    {
        if (MapCollMng::CheckCollision(ray, c).first)
        {
            return false;
        }
    }
    return true;
}

const float Obj::GetSpeed(void) const
{
    return speed_;
}

const float Obj::GeSpMag(void) const
{
    return spMag_;
}

//void Obj::SetAnimState(std::string str)
//{
//    anim_->state(str);
//}

void Obj::UpdateComponent(double delta) const
{
    for (auto& comps : componentList_)
    {
        for (auto& comp : comps.second)
        {
            comp.second->Update(delta);
        }
    }
}
