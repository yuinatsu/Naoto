#pragma once
#include <vector>
#include "Transform.h"
class SceneManager;
class SpriteAnimator;
class TurretShot;

class Turret
{

public:

	static constexpr float SCALE = 80.0f;

	// 衝突判定：球体半径
	static constexpr float COLLISION_RADIUS = 200.0f;

	// 被ダメージエフェクト
	static constexpr float TIME_DAMAGED_EFFECT = 2.0f;

	// 砲台ローカル回転稼働角(deg)
	static constexpr float ANGLE_Y_MIN_STAND = -30.0f;
	static constexpr float ANGLE_Y_MAX_STAND = 30.0f;

	// 砲台ローカル稼働量(deg)
	static constexpr float ANGLE_POW_STAND = 0.2f;

	// 砲身ローカル回転稼働角(deg)
	static constexpr float ANGLE_X_MIN_GUN = -10.0f;
	static constexpr float ANGLE_X_MAX_GUN = 20.0f;

	// 砲身ローカル稼働量(deg)
	static constexpr float ANGLE_POW_GUN = 0.2f;

	static constexpr float ATTACK_TIME = 0.15f;

	enum class STATE
	{
		NONE,
		ATTACK,
		DESTROY
	};

	Turret(SceneManager* manager,
		Transform* transformPlayer,
		Transform* transformParent,
		VECTOR localPos,
		VECTOR localAddAxis);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void SyncParent(Transform* transform, VECTOR addAxis);

	const std::vector<TurretShot*> GetShots(void)const;

	bool IsAlive(void);
	VECTOR GetPos(void);
	void Damage(void);

private:

	SceneManager* mSceneManager;

	// 自機
	Transform* mTransformPlayer;

	// ボス
	Transform* mTransformParent;

	// モデル制御の基本情報(砲台)
	Transform mTransformStand;

	// モデル制御の基本情報(砲身)
	Transform mTransformGun;

	// 自身の爆発
	SpriteAnimator* mExplosion;

	// 状態
	STATE mState;

	// 戦艦からの相対座標
	VECTOR mLocalPos;

	// 追加のローカル回転
	VECTOR mLocalAddAxis;

	// 更に追加の砲身ローカル回転
	VECTOR mLocalAddAxisStand;

	// 更に追加の砲身ローカル回転
	VECTOR mLocalAddAxisGun;

	// 耐久力
	int mHp;

	// 被ダメージエフェクト
	float mStepDamaged;

	// 砲台ローカル稼働量(deg)
	float mAnglePowStand;

	// 砲身ローカル稼働量(deg)
	float mAnglePowGun;

	float mAttackTime;

	std::vector<TurretShot*> shots_;

	// 状態遷移
	void ChangeState(STATE state);

};
