#pragma once
#include <functional>
#include "../Component.h"

class Obj;
class CircleCollider;
class FanCollider;
class Collider;
using GetHitFunc = std::function<void(Collider&)>;


// 当たり判定用クラスの基底クラス
class Collider :
	public Component
{
public:

	/// <summary> コンストラクタ </summary>
	/// <param name="getHitFunc"> 当たった時の処理をfunctionで </param>
	/// <param name="owner"> 持ち主 </param>
	Collider(const GetHitFunc& getHitFunc, const std::string& name,Obj& owner);
	virtual ~Collider();

	/// <summary> 対象のコライダーと当たっているかを調べる処理 </summary>
	/// <param name="col"> 対象のコライダー </param>
	virtual void HitCheck(Collider& col) = 0;

	virtual bool HitBoolCheck(Collider& col) = 0;

	/// <summary> 対象のコライダーと当たっているかを調べる処理(押し出しもする) </summary>
	/// <param name="col">対象のコライダー</param>
	virtual bool HitExCheck(Collider& col) = 0;

	/// <summary> サークルコライダーとの当たり判定を調べる </summary>
	/// <param name="col"> サークルコライダー </param>
	/// <returns></returns>
	virtual bool HitCheck(CircleCollider& col) = 0;

	/// <summary> サークルコライダーとの当たり判定を調べる(押し出し) </summary>
	/// <param name="col">サークルコライダー</param>
	/// <returns></returns>
	virtual bool HitExCheck(CircleCollider& col) = 0;

	virtual bool HitCheck(FanCollider& col) = 0;

	Obj& GetOwner() { return owner_; }
	GetHitFunc& GetFunc(void) { return getHitFunc_; }

	bool IsHit(void)const { return hitFlag_; }
	void Hit(void) { hitFlag_ = true; }
	void HitFlagUpdate(void) { hitFlag_ = false; }
protected:
	bool hitFlag_;

	/// <summary> 当たった時の処理をするfunction </summary>
	GetHitFunc getHitFunc_;
private:

	/// <summary> IDを取得する </summary>
	/// <returns> ID </returns>
	ComponentID GetID() const override;
};

