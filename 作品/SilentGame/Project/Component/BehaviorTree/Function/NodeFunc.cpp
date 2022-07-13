#include "../../../Object/Enemy.h"
#include "../../Navi/Navi.h"
#include "../../Navi/PatrolNavi.h"
#include "NodeFunc.h"

NodeState MoveFunc::operator()(Obj& obj, float delta)
{
	// 移動させる
	obj.MovePos(delta);

	// アイドル状態フラグをfalseにする
	obj.SetIdleFlag(false);
	return NodeState::Success;
}

NodeState RotaFunc::operator()(Obj& obj, float delta)
{
	// 敵を回転させる
	dynamic_cast<Enemy&>(obj).Rotation(delta);
	return NodeState::Success;
}


NodeState NaviSetRoutePatrolFunc::operator()(Obj& obj, float delta)
{
	// ナビを取得
	auto& navi = dynamic_cast<Navi&>(obj.GetComponent(ComponentID::Navi, "Navi"));

	// 巡回地点をゴールに経路を探索する
	navi.Search( obj.GetPos(), dynamic_cast<PatrolNavi&>(obj.GetComponent(ComponentID::PatrolNavi, "Patrol")).GetPos());
	return NodeState::Success;
}

NodeState NaviMoveFunc::operator()(Obj& obj, float delta)
{
	// ナビを取得
	auto& navi = dynamic_cast<Navi&>(obj.GetComponent(ComponentID::Navi, "Navi"));

	// ベクトルと正規化したベクトルを用意
	const auto&& moveVec = navi.GetNaviPos() - obj.GetPos();
	auto moveVecN = moveVec.Normalized();
	
	// 長さを比較
	if (moveVec.SqMagnitude() < Math::Square(obj.GetSpeed() * obj.GeSpMag()))
	{
		// 通常の移動ベクトルの方が長いときそのままナビの指示の座標へ
		obj.SetPos(navi.GetNaviPos());
		return NodeState::Success;
	}
	
	// 移動ベクトルをセット
	obj.SetMoveVec(moveVecN);

	// 移動する
	obj.SetPos(obj.GetPos() + (moveVecN * obj.GetSpeed() * obj.GeSpMag()));

	// アイドル状態フラグをfalseにする
	obj.SetIdleFlag(false);

	return NodeState::Success;
}

NodeState PatrolMoveFunc::operator()(Obj& obj, float delta)
{
	// 巡回用のナビを取得
	auto& navi = dynamic_cast<PatrolNavi&>(obj.GetComponent(ComponentID::PatrolNavi, "Patrol"));

	// ベクトルと正規化したものを用意
	const auto&& moveVec = navi.GetMovePos() - obj.GetPos();
	auto moveVecN = moveVec.Normalized();

	// 長さを比較
	if (moveVec.SqMagnitude() < Math::Square(obj.GetSpeed() * obj.GeSpMag()))
	{
		// 通常の移動ベクトルの方が長いときそのままナビの指示の座標へ
		obj.SetPos(navi.GetMovePos());
		return NodeState::Success;
	}

	// 移動ベクトルをセット
	obj.SetMoveVec(moveVecN);

	// 移動する
	obj.SetPos(obj.GetPos() + (moveVecN * obj.GetSpeed() * obj.GeSpMag()));

	// アイドル状態フラグをfalseにする
	obj.SetIdleFlag(false);
	return NodeState::Success;
}

NodeState NaviWaitSearchFunc::operator()(Obj& obj, float delta)
{
	// ナビを取得
	auto& navi = dynamic_cast<Navi&>(obj.GetComponent(ComponentID::Navi, "Navi"));

	// 状態をチェック
	if (navi.GetNaviState() != NaviState::Search)
	{
		// search以外の時成功
		return NodeState::Success;
	}
	// search中なので処理中
	return NodeState::Now;
}


NodeState PatrolNaviStartFunc::operator()(Obj& obj, float delta)
{
	// 巡回用ナビを取得
	auto patrol = dynamic_cast<PatrolNavi*>(&obj.GetComponent(ComponentID::PatrolNavi, "Patrol"));
	if (patrol == nullptr)
	{
		return NodeState::Faild;
	}

	// 巡回を開始する
	patrol->Start();
	return NodeState::Success;
}

NodeState PatrolNaviStopFunc::operator()(Obj& obj, float delta)
{
	// 巡回用ナビを取得
	auto patrol = dynamic_cast<PatrolNavi*>(&obj.GetComponent(ComponentID::PatrolNavi, "Patrol"));
	if (patrol == nullptr)
	{
		return NodeState::Faild;
	}
	// 巡回を停止する
	patrol->Stop();
	return NodeState::Success;
}

NodeState AnimCorrectMoveVecToAnim::operator()(Obj& obj, float delta)
{
	auto enemy = dynamic_cast<Enemy*>(&obj);
	if (enemy == nullptr)
	{
		return NodeState::Faild;
	}
	// アニメーションを補正する
	enemy->CorrectMoveVecToAnim();
	return NodeState::Success;
}



NodeState EnemyRandRotaFunc::operator()(Obj& obj, float delta)
{
	auto enemy = dynamic_cast<Enemy*>(&obj);
	if (enemy == nullptr)
	{
		return NodeState::Faild;
	}
	enemy->SetRotationAngle();
	return NodeState::Success;
}



EnemyStateTimeWait::EnemyStateTimeWait(float inWaitTime) :
	waitTime_{inWaitTime}
{
}

NodeState EnemyStateTimeWait::operator()(Obj& obj, float delta)
{
	// 敵を取得
	auto enemy = dynamic_cast<Enemy*>(&obj);
	if (enemy == nullptr)
	{
		return NodeState::Faild;
	}

	// 時間をチェックする
	if (enemy->GetStateTime() > waitTime_)
	{
		// 待機時間を越えていたら成功
		return NodeState::Success;
	}
	// アイドル状態にする
	obj.SetIdleFlag(true);

	// 時間を越えてないので処理中
	return NodeState::Now;
}

EnemyStateSetFunc::EnemyStateSetFunc(EnemyState state) :
	state_{state}
{
}

NodeState EnemyStateSetFunc::operator()(Obj& obj, float delta)
{
	auto enemy = dynamic_cast<Enemy*>(&obj);
	if (enemy == nullptr)
	{
		return NodeState::Faild;
	}
	// 敵の状態をセットする
	enemy->SetState(state_);
	return NodeState::Success;
}
