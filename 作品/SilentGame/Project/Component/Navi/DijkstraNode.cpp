#include "DijkstraNode.h"

DijkstraNode::DijkstraNode(const Math::Vector2I& pos) :
    pos_{pos}, endFlag_{false},totalCost_{std::numeric_limits<int>::max()}
{
}

DijkstraNode::~DijkstraNode()
{
}

void DijkstraNode::SetTotalCost(const int cost)
{
    totalCost_ = cost;
}

const int DijkstraNode::GetTotalCost(void) const
{
    return totalCost_;
}

bool DijkstraNode::IsEnd(void) const
{
    return endFlag_;
}

void DijkstraNode::End(void)
{
    endFlag_ = true;
}

void DijkstraNode::SetBeforPos(const Math::Vector2I& befor)
{
    beforPos_ = befor;
}

const Math::Vector2I& DijkstraNode::GetBeforPos(void) const
{
    return beforPos_;
}

void DijkstraNode::Clear(void)
{
    beforPos_ = { -1,-1 };
    totalCost_ = std::numeric_limits<int>::max();
    endFlag_ = false;
}

const Math::Vector2I DijkstraNode::GetPos(void) const
{
    return pos_;
}

void DijkstraNode::PushNextNode(std::shared_ptr<DijkstraNode>& node)
{
    nextNode_.emplace_back(node);
}

void DijkstraNode::CheckNextNode(void)
{
    // 自分のコスト+移動量
    int nCost = totalCost_ + 1;

    // 隣接ノードすべてをチェックする
    for (auto& node : nextNode_)
    {
        // 終了したノードかチェック
        if (!node->IsEnd())
        {
            // 終了していないとき
            // 新しいコストが隣接ノードのコストより低いかチェック
            if (nCost < node->GetTotalCost())
            {
                // 新しいコストの方が低いとき

                // 新しいコストをセット
                node->SetTotalCost(nCost);

                // 移動元である現在の升目を入れる
                node->SetBeforPos(pos_);
            }
        }
    }
}


