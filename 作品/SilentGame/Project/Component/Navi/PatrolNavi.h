#pragma once
#include <vector>
#include "../../common/Math.h"
#include "../Component.h"


class TmxObj;

// 巡回用クラス
class PatrolNavi : 
	public Component
{
	using Vector2lVec = std::vector<Math::Vector2I>;
	using Vector2lVecItr = Vector2lVec::iterator;
public:
	PatrolNavi(Vector2lVec& route,std::shared_ptr<TmxObj>& tmxObj, const std::string& name, Obj& owner);

	/// <summary> 次行くべき座標を取得する </summary>
	/// <param name=""></param>
	/// <returns> 座標 </returns>
	const Math::Vector2 GetMovePos(void) const;

	/// <summary> 現在のマス目 </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const Math::Vector2I& GetPos(void)const;

	/// <summary> 停止しているか </summary>
	/// <param name=""></param>
	/// <returns> 停止しているときtrueしていないときfalse </returns>
	bool IsStop(void) const;

	/// <summary> 停止させる </summary>
	/// <param name=""></param>
	void Stop(void);

	/// <summary> 巡回を開始する </summary>
	/// <param name=""></param>
	void Start(void);

private:

	void Update(float delta) override;

	ComponentID GetID() const;

	// マップ情報
	std::shared_ptr<TmxObj> tmxObj_;

	// 巡回用ルート
	Vector2lVec patrolRoute_;

	// 巡回のマス目
	Vector2lVecItr patrolPos_;

	// 停止フラグ
	bool stopFlag_;
};

