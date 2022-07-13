#pragma once
#include <memory>
#include <list>
#include "../../common/Math.h"

// ダイクストラ法で使うノード
class DijkstraNode
{
public:
	DijkstraNode(const Math::Vector2I& pos);
	~DijkstraNode();

	/// <summary> トータルコストをセットす </summary>
	/// <param name="cost"> トータルコスト </param>
	void SetTotalCost(const int cost);

	/// <summary> トータルコストを取得する </summary>
	/// <param name=""></param>
	/// <returns> トータルコスト </returns>
	const int GetTotalCost(void) const;

	/// <summary> 探索を終了したノードか？ </summary>
	/// <param name=""></param>
	/// <returns> 終了時true終了していないときfalse </returns>
	bool IsEnd(void) const;

	/// <summary> 終了させる </summary>
	/// <param name=""></param>
	void End(void);

	/// <summary> 移動元のノードの升目をセットする </summary>
	/// <param name="befor"></param>
	void SetBeforPos(const Math::Vector2I& befor);

	/// <summary> 移動元のノードの升目を取得する </summary>
	/// <param name=""></param>
	/// <returns> 移動元のノードの升目 </returns>
	const Math::Vector2I& GetBeforPos(void) const;

	/// <summary> 探索開始前にコスト等を初期化する </summary>
	/// <param name=""></param>
	void Clear(void);

	/// <summary> ノードの升目を取得する </summary>
	/// <param name=""></param>
	/// <returns> このノードの升目 </returns>
	const Math::Vector2I GetPos(void) const;

	/// <summary> 隣接ノードを追加する </summary>
	/// <param name="node"> 追加するノード </param>
	void PushNextNode(std::shared_ptr<DijkstraNode>& node);

	/// <summary> ダイクストラ法により隣接ノードのコストを更新する </summary>
	/// <param name=""></param>
	void CheckNextNode(void);
private:

	// 隣接ノード
	std::list<std::shared_ptr< DijkstraNode>> nextNode_;

	// ノードの升目
	Math::Vector2I pos_;

	// 移動元ノードの升目
	Math::Vector2I beforPos_;

	// 終了フラグ
	bool endFlag_;

	// トータルコスト
	int totalCost_;
};

