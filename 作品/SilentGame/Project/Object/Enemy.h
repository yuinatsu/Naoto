#pragma once
#include <memory>
#include "../common/Math.h"
#include "../common/Random.h"
#include "EnemyState.h"
#include "Unit.h"

class Random;
class  CameraMng;
struct Fan;



class TmxObj;

class Enemy :
	public Unit
{
public:
	Enemy(std::vector<Math::Vector2I>& route,std::shared_ptr<TmxObj>& tmxObj, const Math::Vector2& pos);
	~Enemy();

	/// <summary> 敵の状態を取得 </summary>
	/// <param name=""></param>
	/// <returns> 敵の状態 </returns>
	EnemyState GetEnemyState(void) const;

	/// <summary> 敵の状態をセットする </summary>
	/// <param name="state"> セットしたい状態 </param>
	void SetState(EnemyState state);

	/// <summary> 回転角度を設定する </summary>
	/// <param name="angle"> 回転終了角度 </param>
	void SetRotationAngle(float angle);

	/// <summary> 適当に回転させる </summary>
	/// <param name=""></param>
	void SetRotationAngle(void);

	/// <summary> 回転させる </summary>
	/// <param name="delta"></param>
	void Rotation(double delta);

	/// <summary> 移動方向からアニメーションを切り替える </summary>
	/// <param name=""></param>
	void CorrectMoveVecToAnim(void);

	const float GetStateTime(void) const;
private:
	bool Init(void);
	void Update(double delta) override; 
	void Draw(const Math::Vector2& offset)override;

	ObjID GetObjID(void) override { return ObjID::Enemy; };      // idの取得


	// 敵の状態
	EnemyState state_;

	// 振り向き速度
	const float rotSpeed_ = Math::Deg2Rad(5.0f);

	// 振り向く角度
	float targetAngle_ = 0.0f;

	// 振り向く左右どちらか
	float angleSing_ = 1.0f;

	// 現在のステートになってからの経過時間
	float stateTime_;

	friend struct EnemyCheckAngleFunc;

};

