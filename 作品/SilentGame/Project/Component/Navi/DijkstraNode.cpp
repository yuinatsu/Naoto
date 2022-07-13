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
    // �����̃R�X�g+�ړ���
    int nCost = totalCost_ + 1;

    // �אڃm�[�h���ׂĂ��`�F�b�N����
    for (auto& node : nextNode_)
    {
        // �I�������m�[�h���`�F�b�N
        if (!node->IsEnd())
        {
            // �I�����Ă��Ȃ��Ƃ�
            // �V�����R�X�g���אڃm�[�h�̃R�X�g���Ⴂ���`�F�b�N
            if (nCost < node->GetTotalCost())
            {
                // �V�����R�X�g�̕����Ⴂ�Ƃ�

                // �V�����R�X�g���Z�b�g
                node->SetTotalCost(nCost);

                // �ړ����ł��錻�݂̏��ڂ�����
                node->SetBeforPos(pos_);
            }
        }
    }
}


