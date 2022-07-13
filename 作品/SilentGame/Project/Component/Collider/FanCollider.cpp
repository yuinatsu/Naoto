#include "../../Object/Obj.h"
#include "CircleCollider.h"
#include "FanCollider.h"
#include "../../common/MapCollMng.h"
#ifdef _DEBUG
#include <DxLib.h>
constexpr VECTOR V2V(const Math::Vector2& v)
{
	return { v.x,v.y, 0.0f };
}
#endif



FanCollider::FanCollider(std::shared_ptr<TmxObj> tmxObj,float r, float angle, const GetHitFunc& getHitFunc, const std::string& name, Obj& obj) :
	Collider{ getHitFunc,name,obj }, v1_{ r,0.0f }, v2_{ r * std::cos(angle), r * std::sin(angle) }, defLength_{r},  tmxObj_{ tmxObj }
{
}

FanCollider::FanCollider(std::shared_ptr<TmxObj> tmxObj,const Math::Vector2& inv1, const Math::Vector2& inv2, const GetHitFunc& getHitFunc, const std::string& name, Obj& obj) :
	Collider{ getHitFunc,name,obj }, v1_{ inv1 }, v2_{ inv2 }, tmxObj_{ tmxObj }
{
	defLength_ = v1_.Magnitude();
}

void FanCollider::AddAngle(const float angle)
{
	auto vf1 = v1_;
	auto vf2 = v2_;
	float tmpanglev1 = Math::GetAngle2Vector(v2_, v1_);
	float tmpAnglev2 = Math::GetAngle2Vector(v1_, v2_);
	v1_ = Math::RotateMat(tmpanglev1 + angle) * vf2;
	v2_ = Math::RotateMat(tmpAnglev2 + angle) * vf1;

	/*float tmpangle = Math::GetAngle2Vector(vv1_, vv2_);
	vv2_ = Math::RotateMat(tmpangle + angle) * vv1_;*/
}

void FanCollider::SetAngleFromVec(const Math::Vector2& inv1, const Math::Vector2& inv2)
{
	v1_ = inv1 * defLength_;
	v2_ = inv2 * defLength_;
}

bool FanCollider::HitCheck(const Math::Vector2& pos)
{
	//float diff = (pos - owner_.GetPos()).SqMagnitude();
	//// 半径外にいるかどうかを調べる
	//if (diff > v1_.SqMagnitude() + 16)
	//{
	//	return false;
	//}
	//// 中心点が扇形のv1とv2の間に入っていれば確定当たり
	//auto v = pos - owner_.GetPos();
	//auto betAngle = Math::GetAngle2Vector(v1_, v2_);
	//if (Math::GetAngle2Vector(v1_, v) < betAngle)
	//{
	//	return true;
	//}
	//// それぞれの線分との距離を測る
	//// v1
	//if ((v - v1_ * Math::Clamp(Math::Dot(v, v1_) / v1_.SqMagnitude(), 0.0f, 1.0f)).Magnitude() <= 16)
	//{
	//	return true;
	//}
	//// v2
	//if ((v - v2_ * Math::Clamp(Dot(v, v2_) / v2_.SqMagnitude(), 0.0f, 1.0f)).Magnitude() <= 16)
	//{
	//	return true;
	//}
	//return false;
	Math::Vector2 p1 = (owner_.GetPos() + v1_) - owner_.GetPos();
	

	if (Math::Cross(p1,pos - owner_.GetPos()) < 0.0f)
	{
		return false;
	}
	Math::Vector2 p2 = (owner_.GetPos() + v2_) - (owner_.GetPos() + v1_);
	if (Math::Cross(p2,pos - (owner_.GetPos() + v1_)) < 0.0f)
	{
		return false;
	}
	Math::Vector2 p3 = owner_.GetPos() - (owner_.GetPos() + v2_);
	if (Math::Cross(p3,pos - (owner_.GetPos() + v2_)) < 0.0f)
	{
		return false;
	}
	return true;
}

void FanCollider::Update(float delta)
{

	MapCollMng::Ray lray{ owner_.GetPos(), v1_ };
	MapCollMng::Ray rray{ owner_.GetPos(), v2_ };
	for (auto& col : tmxObj_->GetColList())
	{
		auto [flagl,lvec] = MapCollMng::CheckCollision(lray, col);
		v1_ = flagl ? lvec : v1_.Normalized() * defLength_;
		auto [flagr, rvec] = MapCollMng::CheckCollision(rray, col);
		v2_ = flagr ? rvec : v2_.Normalized() * defLength_;
		if (flagr || flagl)
		{
			return;
		}
	}
}


#ifdef _DEBUG
void FanCollider::DbgDraw(const Math::Vector2& offset) const
{
	//auto color = 0xff0000;
	//constexpr float min_angle = DX_PI_F / 36.0f;	// だいたい５度
	//float angle = Math::GetAngle2Vector(v1_, v2_);

	//int triangles_num = static_cast<int>(ceil(angle / min_angle));
	//std::vector<VERTEX2D> v(3 * triangles_num);

	//for (auto& e : v)
	//{
	//	e.rhw = 1.0f;
	//	e.dif = GetColorU8(color >> 16 & 0xff, color >> 8 & 0xff, color & 0xff, 255);
	//	e.u = 0;
	//	e.v = 0;
	//}
	//auto vstart = v1_;
	//auto vend = Math::RotateMat(min_angle) * v1_;
	//for (size_t i = 0; i < triangles_num; i++)
	//{
	//	if (i < triangles_num - 1)
	//	{
	//		v[i * 3 + 0].pos = V2V(owner_.GetPos() + offset);
	//		v[i * 3 + 1].pos = V2V(owner_.GetPos() + offset + vstart);
	//		v[i * 3 + 2].pos = V2V(owner_.GetPos() + offset + vend);
	//	}
	//	else
	//	{
	//		v[i * 3 + 0].pos = V2V(owner_.GetPos() + offset);
	//		v[i * 3 + 1].pos = V2V(owner_.GetPos() + offset + vstart);
	//		v[i * 3 + 2].pos = V2V(owner_.GetPos() + offset + v2_);
	//	}
	//	vstart = vend;
	//	vend = Math::RotateMat(min_angle) * vstart;
	//}
	//// 2Dのポリゴンを描画
	//DrawPrimitive2D(v.data(), v.size(), DX_PRIMTYPE_TRIANGLELIST, DX_NONE_GRAPH, true);
	//Math::Vector2 p = owner_.GetPos() + offset + v1_;
	//DrawLine(owner_.GetPos().x + offset.x, owner_.GetPos().y + offset.y, p.x, p.y, color);
	//p = owner_.GetPos() + v2_ + offset;
	//DrawLine(owner_.GetPos().x + offset.x, owner_.GetPos().y + offset.y, p.x, p.y, color);

	Math::Vector2 p1 = (owner_.GetPos() + v1_) - owner_.GetPos();
	Math::Vector2 p2 = (owner_.GetPos() + v2_) - (owner_.GetPos() + v2_);
	Math::Vector2 p3 = owner_.GetPos() - (owner_.GetPos() + v1_);
	//Math::Vector2 target = pos - owner_.GetPos();
	DrawLine(owner_.GetPos().x + offset.x, owner_.GetPos().y + offset.y, (owner_.GetPos() + v1_).x + offset.x, (owner_.GetPos() + v1_).y + offset.y, 0xff0000);
	DrawLine((owner_.GetPos() + v1_).x + offset.x, (owner_.GetPos() + v1_).y + offset.y, (owner_.GetPos() + v2_).x + offset.x, (owner_.GetPos() + v2_).y + offset.y, 0xff0000);
	DrawLine((owner_.GetPos() + v2_).x + offset.x, (owner_.GetPos() + v2_).y + offset.y, owner_.GetPos().x + offset.x, owner_.GetPos().y + offset.y, 0xff0000);
}

#endif

void FanCollider::HitCheck(Collider& col)
{
	HitFlagUpdate();
	col.HitFlagUpdate();
	if (col.HitCheck(*this))
	{
		getHitFunc_(col);
		col.GetFunc()(*this);
		hitFlag_ = true;
		col.Hit();
	}
}

bool FanCollider::HitExCheck(Collider& col)
{
	return false;
}

bool FanCollider::HitCheck(CircleCollider& col)
{
	return HitCheck(col.GetOwner().GetPos());
}

bool FanCollider::HitExCheck(CircleCollider& col)
{
	return false;
}

bool FanCollider::HitCheck(FanCollider& col)
{
	return false;
}
