#pragma once
#include <map>
#include <vector>
#include <string>
#include "../common/Math.h"
#include "Component.h"

using AnimVector = std::vector<std::pair<int, int>>;

enum class State
{
	Idle,
	Down,
	Left,
	Right,
	Up,
	Dash,
	Crouch,
	Attack,
	Max
};

class Animation :
	public Component
{
public:
	Animation(const std::string& key, const std::string& name, Obj& owner);
	Animation(const std::string& key, const std::string& name, std::pair<int, std::string> id, Obj& owner);
	~Animation();
	bool Init(void);											// 初期化
	void Update(float delta) override;											// 更新
	bool Draw(Math::Vector2 pos, Math::Vector2I size, bool flag);		// 描画 Draw(座標, サイズ, 方向)
	bool Draw(Math::Vector2 pos, Math::Vector2I size, std::string state);		// 描画 Draw(座標, サイズ, 方向)
	bool state(const std::string state);						// ステータス state(ステータス名)
	std::string GetKey(void);									// キー情報取得
	std::string GetState(void);									// ステータス取得
private:

	ComponentID GetID() const override;

	std::string key_;
	std::string state_;
	int animFrame_;
	int animCount_;
};

