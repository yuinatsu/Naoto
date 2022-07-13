#pragma once

enum class EnemyState
{
	Trace,       // 視界に関する状態の時
	Sound,       // 音に反応したときの状態
	Gimic,      // ギミックに対する反応を示した時の反応
	Patrol,       // 巡回中
	MovePatrol,   // 巡回地点に戻るために移動する移動する
	Item,		// 妨害をくらった時の反応
	Non,         // 何もない
	Lost,		// 見失った時や警戒している時の反応
	Look,		// 発見下瞬間の状態
};
