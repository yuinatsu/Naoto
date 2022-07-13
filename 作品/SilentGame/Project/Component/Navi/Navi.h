#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include <list>
#include <mutex>
#include <thread>

#include "../../common/Math.h"
#include "../Component.h"

//class DijkstraNode;
//using DijkstraNodeData = std::vector < std::vector<std::shared_ptr<DijkstraNode>>>;

// A*用ノード
class AstarNode;

// A*用ノードのデータ用
using AstarNodeData = std::vector < std::vector<std::shared_ptr<AstarNode>>>;


class TmxObj;

enum class NaviState
{
	Search,		// 探索中
	Find,		// 目的地が存在するとき
	Non,		// 何もしない止まっとく
};

// 経路探索用クラス
class Navi :
	public Component
{
	using Vector2lVec = std::list<Math::Vector2I>;
	using Vector2lVecItr = Vector2lVec::iterator;
public:
	Navi(std::shared_ptr<TmxObj>& tmxObj,const std::string& name, Obj& owner);
	~Navi();

	/// <summary> スタートからゴールまでの経路の探索 </summary>
	/// <param name="start"> スタート地点の座標 </param>
	/// <param name="goal"> ゴール地点の升目 </param>
	void Search(const Math::Vector2& start, const Math::Vector2I& goal);

	void Search(const Math::Vector2& start, const Math::Vector2& goal);

	/// <summary> Naviクラスの状態を取得する </summary>
	/// <param name=""></param>
	/// <returns> Naviクラスの状態 </returns>
	NaviState GetNaviState(void);

	bool SetNaviState(NaviState state);

	// 結果の取得(デバッグ用)
	std::list<Math::Vector2I>& GetResult();

	// 次行くべき座標
	const Math::Vector2 GetNaviPos(void);
private:

	void Update(float delta) override;

	/// <summary> ノードの作成 </summary>
	/// <param name="tmxObj"></param>
	//void CreateNode(void);

	
	/// <summary> A*探査用のノードを作成 </summary>
	/// <param name=""></param>
	void CreateAstarNode(void);

	// void DijkstraSearch(const Math::Vector2I& start, const Math::Vector2I& goal);

	/// <summary> A*法を使って経路探索を行う </summary>
	/// <param name="start"> 開始マス目 </param>
	/// <param name="goal"> 目的のマス目 </param>
	void AstarSearch(const Math::Vector2I& start, const Math::Vector2I& goal);

	ComponentID GetID() const override;

	// 現在の目的地のマス目
	Vector2lVecItr nowNaviPos_;


	// 探査結果
	Vector2lVec destRoute_;

	// ノード(Astar用ノード)
	AstarNodeData astarNodeData_;

	// マップに関するTmxオブジェクト
	std::shared_ptr<TmxObj> tmxObj_;

	// 探索作業を行うスレッド
	std::thread workThread_;

	// ミューテックス
	std::mutex mutex_;

	// 状態
	NaviState state_;
};

