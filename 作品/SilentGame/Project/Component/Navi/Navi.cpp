#include <algorithm>
// #include "DijkstraNode.h"

#include "AstarNode.h"
#include "../../Resource/Tmx/TmxObj.h"
#include "../../Object/Obj.h"
#include "Navi.h"

#include "../../common/Debug.h"

Navi::Navi(std::shared_ptr<TmxObj>& tmxObj, const std::string& name, Obj& owner) :
	Component{name,owner}, tmxObj_{tmxObj}
{
	// ノードの作成
	CreateAstarNode();

	state_ = NaviState::Non;

}

Navi::~Navi()
{

	// スレッドが実行中かチェック
	if (workThread_.joinable())
	{
		// 実行中の時スレッドを手放す
		workThread_.detach();
	}
}

void Navi::Search(const Math::Vector2& start, const Math::Vector2I& goal)
{
	state_ = NaviState::Search;
	if (workThread_.joinable())
	{
		workThread_.detach();
	}
	// 探索関数を作業用スレッドで開始する
	workThread_ = std::thread{ &Navi::AstarSearch , this, static_cast<Math::Vector2I>(start)/tmxObj_->GetTileSize(), goal};
}

void Navi::Search(const Math::Vector2& start, const Math::Vector2& goal)
{
	Search(start, static_cast<Math::Vector2I>(goal) / tmxObj_->GetTileSize());
}

NaviState Navi::GetNaviState(void)
{
	std::unique_lock<std::mutex> ulock(mutex_, std::defer_lock);

	// ロックできるかをチェック
	if (ulock.try_lock())
	{
		// ロックできるとき

		// スレッドが使われているかチェック
		if (workThread_.joinable() && state_ == NaviState::Find)
		{
			// 処理が終わっているので同期
			workThread_.join();
		}
		return state_;
	}

	return NaviState::Search;

}

bool Navi::SetNaviState(NaviState state)
{
	std::unique_lock<std::mutex> ulock(mutex_, std::defer_lock);

	// ロックできるかをチェック
	if (!ulock.try_lock())
	{
		return false;
	}
	state_ = state;
	return true;
}


std::list<Math::Vector2I>& Navi::GetResult()
{
	std::lock_guard<std::mutex>lock(mutex_);
	return destRoute_;
}



const Math::Vector2 Navi::GetNaviPos(void)
{
	std::lock_guard<std::mutex>lock(mutex_);
	return static_cast<Math::Vector2>(*nowNaviPos_ * tmxObj_->GetTileSize() + (tmxObj_->GetTileSize() / 2));
}

void Navi::Update(float delta)
{
	// ステートを調べる
	if (GetNaviState() == NaviState::Find)
	{
		// 目的地がある時
		auto& tileSize = tmxObj_->GetTileSize();
		const auto& nowPos = static_cast<Math::Vector2I>(owner_.GetPos())/ tileSize;

		// GetNaviPos()/tileSize - owner_.GetPos();
		// 現在のマス目をチェック
		if (nowPos == *nowNaviPos_)
		{
			
			// 次のマス目へ行くため進める
			++nowNaviPos_;
			if (nowNaviPos_ == destRoute_.end())
			{
				// 末端の時到着なので終了
				state_ = NaviState::Non;
				return;
			}
		}
	}
}

//void Navi::CreateNode()
//{
//	// ノードデータをリサイズ
//	nodeData_.resize(tmxObj_.GetWorldArea().y);
//	for (auto& v : nodeData_)
//	{
//		v.resize(tmxObj_.GetWorldArea().x);
//	}
//
//	// ノードを生成
//	for (int y = 0; y < tmxObj_.GetWorldArea().y; y++)
//	{
//		for (int x = 0; x < tmxObj_.GetWorldArea().x; x++)
//		{
//			// 壁や床に関してのチェック
//			if (tmxObj_.GetMapData("2Block", x, y) != 0 || tmxObj_.GetMapData("1Floor",x,y) == 0)
//			{
//				// 壁があるもしくは範囲外の時nullptr
//				nodeData_[y][x] = nullptr;
//			}
//			else
//			{
//				// 移動できるのでノードを作成
//				nodeData_[y][x] = std::make_shared<DijkstraNode>(Math::Vector2I{ x,y });
//			}
//		}
//	}
//
//	// 範囲をチェックして隣接ノードを入れるラムダ式
//	auto ckFunc = [this](int x, int y, int tx, int ty) {
//		// 範囲チェック
//		if (tx < 0 || tx > tmxObj_.GetWorldArea().x || ty < 0 || ty > tmxObj_.GetWorldArea().y)
//		{
//			// 何もせず終了
//			return;
//		}
//
//		// 隣接ノードが存在をチェック
//		if (nodeData_[ty][tx] == nullptr)
//		{
//			// 隣接ノードがないとき終了
//			return;
//		}
//
//		// 隣接ノードを入れる
//		nodeData_[y][x]->PushNextNode(nodeData_[ty][tx]);
//	};
//
//	// 隣接ノードをセットする
//	for (int y = 0; y < tmxObj_.GetWorldArea().y; y++)
//	{
//		for (int x = 0; x < tmxObj_.GetWorldArea().x; x++)
//		{
//			// ノードが存在するかチェック
//			if (nodeData_[y][x] == nullptr)
//			{
//				continue;
//			}
//
//			// 左
//			ckFunc(x, y, x - 1, y);
//
//			// 右
//			ckFunc(x, y, x + 1, y);
//
//			// 下
//			ckFunc(x, y, x, y + 1);
//
//			// 上
//			ckFunc(x, y, x, y - 1);
//		}
//	}
//}

void Navi::CreateAstarNode(void)
{
	// ノードデータをリサイズ
	astarNodeData_.resize(tmxObj_->GetWorldArea().y);
	for (auto& v : astarNodeData_)
	{
		v.resize(tmxObj_->GetWorldArea().x);
	}

	// ノードを生成
	for (int y = 0; y < tmxObj_->GetWorldArea().y; y++)
	{
		for (int x = 0; x < tmxObj_->GetWorldArea().x; x++)
		{
			// 壁や床に関してのチェック
			if (tmxObj_->GetMapData("2Block", x, y) != 0 || tmxObj_->GetMapData("1Floor", x, y) == 0)
			{
				// 壁があるもしくは範囲外の時nullptr
				astarNodeData_[y][x] = nullptr;
			}
			else
			{
				// 移動できるのでノードを作成
				astarNodeData_[y][x] = std::make_shared<AstarNode>(Math::Vector2I{ x,y });
			}
		}
	}

	// 範囲をチェックして隣接ノードを入れるラムダ式
	auto ckFunc = [this](int x, int y, int tx, int ty) {
		// 範囲チェック
		if (tx < 0 || tx > tmxObj_->GetWorldArea().x || ty < 0 || ty > tmxObj_->GetWorldArea().y)
		{
			// 何もせず終了
			return;
		}

		// 隣接ノードが存在をチェック
		if (astarNodeData_[ty][tx] == nullptr)
		{
			// 隣接ノードがないとき終了
			return;
		}

		// 隣接ノードを入れる
		astarNodeData_[y][x]->PushNextNode(astarNodeData_[ty][tx]);
	};

	// 隣接ノードをセットする
	for (int y = 0; y < tmxObj_->GetWorldArea().y; y++)
	{
		for (int x = 0; x < tmxObj_->GetWorldArea().x; x++)
		{
			// ノードが存在するかチェック
			if (astarNodeData_[y][x] == nullptr)
			{
				continue;
			}

			// 左
			ckFunc(x, y, x - 1, y);

			// 右
			ckFunc(x, y, x + 1, y);

			// 下
			ckFunc(x, y, x, y + 1);

			// 上
			ckFunc(x, y, x, y - 1);
		}
	}
}

//void Navi::DijkstraSearch(const Math::Vector2I& start, const Math::Vector2I& goal)
//{
//	mutex_.lock();
//	// ノードを初期化
//	std::for_each(nodeData_.begin(), nodeData_.end(),
//		[](auto& data)
//		{
//			std::for_each(data.begin(), data.end(), [](auto& node) {
//				if (node != nullptr)
//				{
//					node->Clear();
//				}
//				});
//		}
//	);
//
//
//	if (nodeData_[start.y][start.x] == nullptr)
//	{
//		mutex_.unlock();
//		return;
//	}
//	// スタート地点のコストをゼロにする
//	nodeData_[start.y][start.x]->SetTotalCost(0);
//	nodeData_[start.y][start.x]->SetBeforPos({ -1,-1 });
//
//	// チェックするノードをリスト化
//	std::list<std::shared_ptr<DijkstraNode>> targetList;
//	for (auto& v : nodeData_)
//	{
//		for (auto& n : v)
//		{
//			if (n != nullptr)
//			{
//				targetList.emplace_back(n);
//			}
//		}
//	}
//
//	// ソート用ラムダ
//	auto sortFunc = [](std::shared_ptr<DijkstraNode>& nodeA, std::shared_ptr<DijkstraNode>& nodeB)
//	{
//		return nodeA->GetTotalCost() < nodeB->GetTotalCost();
//	};
//
//	// コスト順にソート
//	targetList.sort(sortFunc);
//
//
//	std::shared_ptr<DijkstraNode> node;
//	while (true)
//	{
//		// 先頭を取り出す
//		node = *targetList.begin();
//
//		// 取り出した先頭のノードをチェックすべきリストから外す
//		targetList.pop_front();
//
//		// 隣接するノードチェックする
//		node->CheckNextNode();
//
//		// ノードに探査終了フラグを立てる
//		node->End();
//
//		if (targetList.size() <= 0)
//		{
//			break;
//		}
//
//		// コスト昇順でソートする
//		targetList.sort(sortFunc);
//	}
//
//	// 結果を初期化
//	destRoute_.clear();
//
//	// ゴールからたどって行く
//	destRoute_.emplace_back(nodeData_[goal.y][goal.x]->GetPos());
//	for (
//		auto pos = nodeData_[goal.y][goal.x]->GetBeforPos();
//		!(pos == Math::Vector2I{ -1,-1 });
//		pos = nodeData_[pos.y][pos.x]->GetBeforPos()
//		)
//	{
//		destRoute_.emplace_back(pos);
//	}
//	flag_ = true;
//	state_ = NaviState::MoveDest;
//	mutex_.unlock();
//}

void Navi::AstarSearch(const Math::Vector2I& start, const Math::Vector2I& goal)
{
	std::lock_guard<std::mutex> lock(mutex_);

	// 今持っている結果を初期化
	destRoute_.clear();

	// スタートとゴールが同じか
	if (start == goal)
	{
		// 同じときゴールだけ入れる
		destRoute_.emplace_back(goal);
		nowNaviPos_ = destRoute_.begin();
		state_ = NaviState::Find;
		return;
	}

	// ノードの情報を初期化
	std::for_each(astarNodeData_.begin(), astarNodeData_.end(),
		[](auto& data)
		{
			std::for_each(data.begin(), data.end(), [](auto& node) {
				if (node != nullptr)
				{
					node->Clear();
				}
				});
		}
	);

	// ソート用ラムダ
	auto sortFunc = [](std::shared_ptr<AstarNode>& nodeA, std::shared_ptr<AstarNode>& nodeB)
	{
		return nodeA->GetTotalCost() < nodeB->GetTotalCost();
	};

	// オープンリスト
	std::list<std::shared_ptr<AstarNode>> openList;

	// クローズリスト
	std::list<std::shared_ptr<AstarNode>> closeList;

	// オープンリストにスタートノードを入れる
	if (astarNodeData_[start.y][start.x] == nullptr)
	{
		state_ = NaviState::Non;
		return;
	}
	openList.emplace_back(astarNodeData_[start.y][start.x]);

	// チェックするノード
	std::shared_ptr<AstarNode> node;

	// 結果を一時的に入れておくための変数
	std::vector<std::vector<Math::Vector2I>> result;

	// 総マス目数を取得
	const auto& num = tmxObj_->GetWorldArea();

	// 結果用変数をリサイズして初期化
	result.resize(num.y);
	for (auto& vec : result)
	{
		vec.resize(num.x);
		std::fill(vec.begin(), vec.end(), Math::Vector2I{ -1,-1 });
	}

	// チェック用ラムダ
	auto ckFunc = [](std::list<std::shared_ptr<AstarNode>>& ckList,const std::shared_ptr<AstarNode>& node, float cost) {
		auto itr = std::find_if(
			ckList.begin(), ckList.end(),
			[&node](std::shared_ptr<AstarNode>& n) { return (n->GetPos() == node->GetPos()); }
		);

		// 同じノードがあるかチェック
		if (itr != ckList.end())
		{
			// 同じノードがある時
			// コストをチェック
			if ((*itr)->GetTotalCost() > cost)
			{
				// リストにある方がコストが高い時削除して終わる
				ckList.erase(itr);
				return false;
			}
			return true;
		}
		return false;
	};

	while (!openList.empty())
	{
		// リストの一番先頭を取得
		node = *openList.begin();

		// 取得したやつを削除
		openList.pop_front();

		// ゴールかどうかチェック
		if (node->GetPos() == goal)
		{
			// ゴールの時クローズリストに入れてループを抜ける
			closeList.emplace_back(node);
			break;
		}

		// 隣接ノードをオープンリストに入れる
		for (auto& next : node->GetNextNode())
		{
		
			// ヒューリスティックコストを計算
			next->CalculateHeuristicCost(goal);

			// 新しいコストを計算
			float ncost = 1.0f + next->GetHeuristicCost() + node->GetTotalCost();

			// リストに同じノードが存在してリストの方がコストが高い場合削除
			
			// リストをチェック
			if (!ckFunc(closeList, next, ncost) && !ckFunc(openList, next, ncost))
			{
				// 同じノードが無いもしくはあっても新しいコストが低いとき追加
				next->SetTotalCost(ncost);
				result[next->GetPos().y][next->GetPos().x] = node->GetPos();
				openList.emplace_back(next);
			}
			
		}

		// クローズリストに同じノードがあるか探す
		auto itr = std::find_if(closeList.begin(), closeList.end(), [&node](std::shared_ptr<AstarNode>& n) { return n->GetPos() == node->GetPos(); });

		if (itr == closeList.end())
		{
			// 同じノードがないときノードの探索を終了なのでクローズリストに入れる
			closeList.emplace_back(node);
		}
		// オープンリストをソートする
		openList.sort(sortFunc);

		
	}

	// 結果を格納する
	destRoute_.emplace_back(goal);
	auto& p = result[goal.y][goal.x];
	while (true)
	{
		
		if (p == start)
		{
			destRoute_.emplace_back(p);
			state_ = NaviState::Find;
			break;
		}
		else if (p == Math::Vector2I{-1,-1})
		{
			state_ = NaviState::Non;
			break;
		}
		destRoute_.emplace_back(p);
		p = result[p.y][p.x];
	}

	destRoute_.reverse();

	state_ = NaviState::Find;

	// 先頭を入れとく
	nowNaviPos_ = destRoute_.begin();
}

ComponentID Navi::GetID() const
{
	return ComponentID::Navi;
}

