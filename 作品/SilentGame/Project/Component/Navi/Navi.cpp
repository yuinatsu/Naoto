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
	// �m�[�h�̍쐬
	CreateAstarNode();

	state_ = NaviState::Non;

}

Navi::~Navi()
{

	// �X���b�h�����s�����`�F�b�N
	if (workThread_.joinable())
	{
		// ���s���̎��X���b�h�������
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
	// �T���֐�����Ɨp�X���b�h�ŊJ�n����
	workThread_ = std::thread{ &Navi::AstarSearch , this, static_cast<Math::Vector2I>(start)/tmxObj_->GetTileSize(), goal};
}

void Navi::Search(const Math::Vector2& start, const Math::Vector2& goal)
{
	Search(start, static_cast<Math::Vector2I>(goal) / tmxObj_->GetTileSize());
}

NaviState Navi::GetNaviState(void)
{
	std::unique_lock<std::mutex> ulock(mutex_, std::defer_lock);

	// ���b�N�ł��邩���`�F�b�N
	if (ulock.try_lock())
	{
		// ���b�N�ł���Ƃ�

		// �X���b�h���g���Ă��邩�`�F�b�N
		if (workThread_.joinable() && state_ == NaviState::Find)
		{
			// �������I����Ă���̂œ���
			workThread_.join();
		}
		return state_;
	}

	return NaviState::Search;

}

bool Navi::SetNaviState(NaviState state)
{
	std::unique_lock<std::mutex> ulock(mutex_, std::defer_lock);

	// ���b�N�ł��邩���`�F�b�N
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
	// �X�e�[�g�𒲂ׂ�
	if (GetNaviState() == NaviState::Find)
	{
		// �ړI�n�����鎞
		auto& tileSize = tmxObj_->GetTileSize();
		const auto& nowPos = static_cast<Math::Vector2I>(owner_.GetPos())/ tileSize;

		// GetNaviPos()/tileSize - owner_.GetPos();
		// ���݂̃}�X�ڂ��`�F�b�N
		if (nowPos == *nowNaviPos_)
		{
			
			// ���̃}�X�ڂ֍s�����ߐi�߂�
			++nowNaviPos_;
			if (nowNaviPos_ == destRoute_.end())
			{
				// ���[�̎������Ȃ̂ŏI��
				state_ = NaviState::Non;
				return;
			}
		}
	}
}

//void Navi::CreateNode()
//{
//	// �m�[�h�f�[�^�����T�C�Y
//	nodeData_.resize(tmxObj_.GetWorldArea().y);
//	for (auto& v : nodeData_)
//	{
//		v.resize(tmxObj_.GetWorldArea().x);
//	}
//
//	// �m�[�h�𐶐�
//	for (int y = 0; y < tmxObj_.GetWorldArea().y; y++)
//	{
//		for (int x = 0; x < tmxObj_.GetWorldArea().x; x++)
//		{
//			// �ǂ⏰�Ɋւ��Ẵ`�F�b�N
//			if (tmxObj_.GetMapData("2Block", x, y) != 0 || tmxObj_.GetMapData("1Floor",x,y) == 0)
//			{
//				// �ǂ�����������͔͈͊O�̎�nullptr
//				nodeData_[y][x] = nullptr;
//			}
//			else
//			{
//				// �ړ��ł���̂Ńm�[�h���쐬
//				nodeData_[y][x] = std::make_shared<DijkstraNode>(Math::Vector2I{ x,y });
//			}
//		}
//	}
//
//	// �͈͂��`�F�b�N���ėאڃm�[�h�����郉���_��
//	auto ckFunc = [this](int x, int y, int tx, int ty) {
//		// �͈̓`�F�b�N
//		if (tx < 0 || tx > tmxObj_.GetWorldArea().x || ty < 0 || ty > tmxObj_.GetWorldArea().y)
//		{
//			// ���������I��
//			return;
//		}
//
//		// �אڃm�[�h�����݂��`�F�b�N
//		if (nodeData_[ty][tx] == nullptr)
//		{
//			// �אڃm�[�h���Ȃ��Ƃ��I��
//			return;
//		}
//
//		// �אڃm�[�h������
//		nodeData_[y][x]->PushNextNode(nodeData_[ty][tx]);
//	};
//
//	// �אڃm�[�h���Z�b�g����
//	for (int y = 0; y < tmxObj_.GetWorldArea().y; y++)
//	{
//		for (int x = 0; x < tmxObj_.GetWorldArea().x; x++)
//		{
//			// �m�[�h�����݂��邩�`�F�b�N
//			if (nodeData_[y][x] == nullptr)
//			{
//				continue;
//			}
//
//			// ��
//			ckFunc(x, y, x - 1, y);
//
//			// �E
//			ckFunc(x, y, x + 1, y);
//
//			// ��
//			ckFunc(x, y, x, y + 1);
//
//			// ��
//			ckFunc(x, y, x, y - 1);
//		}
//	}
//}

void Navi::CreateAstarNode(void)
{
	// �m�[�h�f�[�^�����T�C�Y
	astarNodeData_.resize(tmxObj_->GetWorldArea().y);
	for (auto& v : astarNodeData_)
	{
		v.resize(tmxObj_->GetWorldArea().x);
	}

	// �m�[�h�𐶐�
	for (int y = 0; y < tmxObj_->GetWorldArea().y; y++)
	{
		for (int x = 0; x < tmxObj_->GetWorldArea().x; x++)
		{
			// �ǂ⏰�Ɋւ��Ẵ`�F�b�N
			if (tmxObj_->GetMapData("2Block", x, y) != 0 || tmxObj_->GetMapData("1Floor", x, y) == 0)
			{
				// �ǂ�����������͔͈͊O�̎�nullptr
				astarNodeData_[y][x] = nullptr;
			}
			else
			{
				// �ړ��ł���̂Ńm�[�h���쐬
				astarNodeData_[y][x] = std::make_shared<AstarNode>(Math::Vector2I{ x,y });
			}
		}
	}

	// �͈͂��`�F�b�N���ėאڃm�[�h�����郉���_��
	auto ckFunc = [this](int x, int y, int tx, int ty) {
		// �͈̓`�F�b�N
		if (tx < 0 || tx > tmxObj_->GetWorldArea().x || ty < 0 || ty > tmxObj_->GetWorldArea().y)
		{
			// ���������I��
			return;
		}

		// �אڃm�[�h�����݂��`�F�b�N
		if (astarNodeData_[ty][tx] == nullptr)
		{
			// �אڃm�[�h���Ȃ��Ƃ��I��
			return;
		}

		// �אڃm�[�h������
		astarNodeData_[y][x]->PushNextNode(astarNodeData_[ty][tx]);
	};

	// �אڃm�[�h���Z�b�g����
	for (int y = 0; y < tmxObj_->GetWorldArea().y; y++)
	{
		for (int x = 0; x < tmxObj_->GetWorldArea().x; x++)
		{
			// �m�[�h�����݂��邩�`�F�b�N
			if (astarNodeData_[y][x] == nullptr)
			{
				continue;
			}

			// ��
			ckFunc(x, y, x - 1, y);

			// �E
			ckFunc(x, y, x + 1, y);

			// ��
			ckFunc(x, y, x, y + 1);

			// ��
			ckFunc(x, y, x, y - 1);
		}
	}
}

//void Navi::DijkstraSearch(const Math::Vector2I& start, const Math::Vector2I& goal)
//{
//	mutex_.lock();
//	// �m�[�h��������
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
//	// �X�^�[�g�n�_�̃R�X�g���[���ɂ���
//	nodeData_[start.y][start.x]->SetTotalCost(0);
//	nodeData_[start.y][start.x]->SetBeforPos({ -1,-1 });
//
//	// �`�F�b�N����m�[�h�����X�g��
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
//	// �\�[�g�p�����_
//	auto sortFunc = [](std::shared_ptr<DijkstraNode>& nodeA, std::shared_ptr<DijkstraNode>& nodeB)
//	{
//		return nodeA->GetTotalCost() < nodeB->GetTotalCost();
//	};
//
//	// �R�X�g���Ƀ\�[�g
//	targetList.sort(sortFunc);
//
//
//	std::shared_ptr<DijkstraNode> node;
//	while (true)
//	{
//		// �擪�����o��
//		node = *targetList.begin();
//
//		// ���o�����擪�̃m�[�h���`�F�b�N���ׂ����X�g����O��
//		targetList.pop_front();
//
//		// �אڂ���m�[�h�`�F�b�N����
//		node->CheckNextNode();
//
//		// �m�[�h�ɒT���I���t���O�𗧂Ă�
//		node->End();
//
//		if (targetList.size() <= 0)
//		{
//			break;
//		}
//
//		// �R�X�g�����Ń\�[�g����
//		targetList.sort(sortFunc);
//	}
//
//	// ���ʂ�������
//	destRoute_.clear();
//
//	// �S�[�����炽�ǂ��čs��
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

	// �������Ă��錋�ʂ�������
	destRoute_.clear();

	// �X�^�[�g�ƃS�[����������
	if (start == goal)
	{
		// �����Ƃ��S�[�����������
		destRoute_.emplace_back(goal);
		nowNaviPos_ = destRoute_.begin();
		state_ = NaviState::Find;
		return;
	}

	// �m�[�h�̏���������
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

	// �\�[�g�p�����_
	auto sortFunc = [](std::shared_ptr<AstarNode>& nodeA, std::shared_ptr<AstarNode>& nodeB)
	{
		return nodeA->GetTotalCost() < nodeB->GetTotalCost();
	};

	// �I�[�v�����X�g
	std::list<std::shared_ptr<AstarNode>> openList;

	// �N���[�Y���X�g
	std::list<std::shared_ptr<AstarNode>> closeList;

	// �I�[�v�����X�g�ɃX�^�[�g�m�[�h������
	if (astarNodeData_[start.y][start.x] == nullptr)
	{
		state_ = NaviState::Non;
		return;
	}
	openList.emplace_back(astarNodeData_[start.y][start.x]);

	// �`�F�b�N����m�[�h
	std::shared_ptr<AstarNode> node;

	// ���ʂ��ꎞ�I�ɓ���Ă������߂̕ϐ�
	std::vector<std::vector<Math::Vector2I>> result;

	// ���}�X�ڐ����擾
	const auto& num = tmxObj_->GetWorldArea();

	// ���ʗp�ϐ������T�C�Y���ď�����
	result.resize(num.y);
	for (auto& vec : result)
	{
		vec.resize(num.x);
		std::fill(vec.begin(), vec.end(), Math::Vector2I{ -1,-1 });
	}

	// �`�F�b�N�p�����_
	auto ckFunc = [](std::list<std::shared_ptr<AstarNode>>& ckList,const std::shared_ptr<AstarNode>& node, float cost) {
		auto itr = std::find_if(
			ckList.begin(), ckList.end(),
			[&node](std::shared_ptr<AstarNode>& n) { return (n->GetPos() == node->GetPos()); }
		);

		// �����m�[�h�����邩�`�F�b�N
		if (itr != ckList.end())
		{
			// �����m�[�h�����鎞
			// �R�X�g���`�F�b�N
			if ((*itr)->GetTotalCost() > cost)
			{
				// ���X�g�ɂ�������R�X�g���������폜���ďI���
				ckList.erase(itr);
				return false;
			}
			return true;
		}
		return false;
	};

	while (!openList.empty())
	{
		// ���X�g�̈�Ԑ擪���擾
		node = *openList.begin();

		// �擾��������폜
		openList.pop_front();

		// �S�[�����ǂ����`�F�b�N
		if (node->GetPos() == goal)
		{
			// �S�[���̎��N���[�Y���X�g�ɓ���ă��[�v�𔲂���
			closeList.emplace_back(node);
			break;
		}

		// �אڃm�[�h���I�[�v�����X�g�ɓ����
		for (auto& next : node->GetNextNode())
		{
		
			// �q���[���X�e�B�b�N�R�X�g���v�Z
			next->CalculateHeuristicCost(goal);

			// �V�����R�X�g���v�Z
			float ncost = 1.0f + next->GetHeuristicCost() + node->GetTotalCost();

			// ���X�g�ɓ����m�[�h�����݂��ă��X�g�̕����R�X�g�������ꍇ�폜
			
			// ���X�g���`�F�b�N
			if (!ckFunc(closeList, next, ncost) && !ckFunc(openList, next, ncost))
			{
				// �����m�[�h�������������͂����Ă��V�����R�X�g���Ⴂ�Ƃ��ǉ�
				next->SetTotalCost(ncost);
				result[next->GetPos().y][next->GetPos().x] = node->GetPos();
				openList.emplace_back(next);
			}
			
		}

		// �N���[�Y���X�g�ɓ����m�[�h�����邩�T��
		auto itr = std::find_if(closeList.begin(), closeList.end(), [&node](std::shared_ptr<AstarNode>& n) { return n->GetPos() == node->GetPos(); });

		if (itr == closeList.end())
		{
			// �����m�[�h���Ȃ��Ƃ��m�[�h�̒T�����I���Ȃ̂ŃN���[�Y���X�g�ɓ����
			closeList.emplace_back(node);
		}
		// �I�[�v�����X�g���\�[�g����
		openList.sort(sortFunc);

		
	}

	// ���ʂ��i�[����
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

	// �擪�����Ƃ�
	nowNaviPos_ = destRoute_.begin();
}

ComponentID Navi::GetID() const
{
	return ComponentID::Navi;
}

