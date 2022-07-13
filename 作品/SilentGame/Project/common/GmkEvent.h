#pragma once
#include <list>
#include <memory>
#include <functional>
#include <unordered_map>
#include "Math.h"

class Obj;

enum class EventType
{
	Alert,		// 監視カメラとかに見つかった時にサイレンがなるタイプ
	Enemy,				// 敵に見つかった時
	Non,		// 特に何も起きていないとき
};


class GmkEvent
{
	using GmkFuncMap = std::unordered_map < EventType, std::pair<std::function<void(float)>, std::function<void(void)>>>;
public:
	GmkEvent();
	~GmkEvent();
	// プレイヤーを発見した時のイベント
	void DisPlayer(bool flag,float delta);

	void StartEvent(std::list<std::unique_ptr<Obj>>& enemyList, const Math::Vector2& pos,EventType type);

	void Update(float delta);
	void Draw(void);

private:

	// アラートの更新と描画
	void AlertUpdate(float delta);
	void AlertDraw(void);

	// ギミックイベントごとの更新と描画処理をstateで切り替える用に
	GmkFuncMap gmkFunc_;

	// 経過時間
	float gmkStepTime_;

	// 現在のイベントの種類
	EventType nowType_;

	// プレイヤーを見つけて何秒立ったのか
	float Time_;
	// 発見時の描画輝度の調整
	bool flag_;
	float sColor_;
	bool scFlag_;
	// プレイヤーが見つかった時の座標を入れる
	Math::Vector2 sPos_;

};

