#pragma once
#include "../NodeState.h"

class Obj;

// 移動
struct MoveFunc
{
	NodeState operator()(Obj& obj, float delta);
};

// 回転
struct RotaFunc
{
	NodeState operator()(Obj& obj, float delta);
};

// 敵を回転させる
struct EnemyRandRotaFunc
{
	NodeState operator()(Obj& obj, float delta);
};



// Naviの目的地を巡回地点にする
struct NaviSetRoutePatrolFunc
{
	NodeState operator()(Obj& obj, float delta);
};

// Naviに従いObjを移動させる
struct NaviMoveFunc
{
	NodeState operator()(Obj& obj, float delta);
};

// PatrolNaviに従いObjを移動させる
struct PatrolMoveFunc
{
	NodeState operator()(Obj& obj, float delta);
};

// Naviの探索を待機する
struct NaviWaitSearchFunc
{
	NodeState operator()(Obj& obj, float delta);
};

// 巡回を開始する
struct PatrolNaviStartFunc
{
	NodeState operator()(Obj& obj, float delta);
};

// 巡回を停止する
struct PatrolNaviStopFunc
{
	NodeState operator()(Obj& obj, float delta);
};

// MoveVecをもとにアニメーションをセットする
struct AnimCorrectMoveVecToAnim
{
	NodeState operator()(Obj& obj, float delta);
};


// 敵の状態時間が指定時間になるまで待つ処理
struct EnemyStateTimeWait
{
	EnemyStateTimeWait(float inMaxTime);
	NodeState operator()(Obj& obj, float delta);
private:
	const float waitTime_;
};

// 敵の状態をセットする処理
struct EnemyStateSetFunc
{
	EnemyStateSetFunc(EnemyState state);
	NodeState operator()(Obj& obj, float delta);
private:
	const EnemyState state_;

};