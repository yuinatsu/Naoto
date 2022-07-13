#include <sstream>
#include "rapidxml.hpp"
#include "BehaviorTreeLoader.h"
#include "../Component/BehaviorTree/SelectorNode.h"
#include "../Component/BehaviorTree/SequenceNode.h"
#include "../Component/BehaviorTree/ActionNode.h"
#include "../Component/BehaviorTree/ConditionNode.h"

#include "../common/Debug.h"

// �R���f�B�V�����m�[�h�p
#include "../Component/BehaviorTree/Function/ConditionNodeFunc.h"

// �A�N�V�����m�[�h�p
#include "../Component/BehaviorTree/Function/NodeFunc.h"

namespace {
	
	template<class T>
	struct Str2Val
	{
		T operator()(const std::string& str)
		{
			T val;
			std::stringstream ss;
			ss << str;
			ss >> val;
			return val;
		}
	};
}


BehaviorTreeLoader::BehaviorTreeLoader()
{
	createFuncMap_.reserve(4);

	// �Z���N�^�[�m�[�h�쐬�p
	createFuncMap_.try_emplace(
		"SelectorNode",
		[this](rapidxml::xml_node<char>* node) {
			// �Z���N�^�[�m�[�h���쐬
			auto selector = std::make_unique<SelectorNode>();

			// �q�m�[�h�𐶐����Ă���
			for (auto next = node->first_node(); next != nullptr; next = next->next_sibling())
			{
				// �q�m�[�h�𐶐����ē���Ă���
				selector->PushChildren(std::move(createFuncMap_[next->name()](next)));
			}
			return std::move(selector);
		}
	);

	// �V�[�N�G���X�m�[�h�쐬�p
	createFuncMap_.emplace(
		"SequenceNode",
		[this](rapidxml::xml_node<char>* node) {
			// �V�[�N�G���X�m�[�h���쐬
			auto sequence = std::make_unique<SequenceNode>();

			// �q�m�[�h�𐶐����Ă���
			for (auto next = node->first_node(); next != nullptr; next = next->next_sibling())
			{
				// �q�m�[�h�𐶐����ē���Ă���
				sequence->PushChildren(std::move(createFuncMap_[next->name()](next)));
			}
			return std::move(sequence);
		}
	);


	// �A�N�V�����m�[�h�쐬�p
	createFuncMap_.emplace(
		"ActionNode",
		[this](rapidxml::xml_node<char>* node) {

			if (!actFuncMap_.contains(node->first_attribute("FuncName")->value()))
			{
				Assert(false, "���݂��Ȃ��֐��ł�");
			}
			return std::make_unique<ActionNode>(std::move(actFuncMap_[node->first_attribute("FuncName")->value()](node)));
		}
	);

	// �R���f�B�V�����m�[�h�쐬�p
	createFuncMap_.emplace(
		"ConditionNode",
		[this](rapidxml::xml_node<char>* node) {
			if (!ckFuncMap_.contains(node->first_attribute("FuncName")->value()))
			{
				Assert(false, "���݂��Ȃ��֐��ł�");
			}
			return std::make_unique<ConditionNode>(std::move(ckFuncMap_[node->first_attribute("FuncName")->value()](node)));
		}
	);

	CreateActFuncMap();
	CreateCheckFuncMap();

}

BehaviorTreeLoader::~BehaviorTreeLoader()
{
}

std::unique_ptr<BehaviorBaseNode> BehaviorTreeLoader::Load(const std::string& name)
{
	// ���łɍ쐬���Ă��邩�`�F�b�N
	if (nodeMap_.contains(name))
	{
		// �쐬���Ă���ꍇ�͂����Ԃ�
		return nodeMap_[name]->Copy();
	}
	rapidxml::file<> file = name.c_str();
	xmldoc_.parse<0>(file.data());
	auto node = xmldoc_.first_node("rootNode");
	node = node->first_node();

	// �ċA�I�Ƀm�[�h���Ƃɐ����֐����Ă�tree�����
	// �i�[����
	nodeMap_.emplace(name.c_str(), createFuncMap_[node->name()](node));
	return nodeMap_[name]->Copy();
}

void BehaviorTreeLoader::CreateActFuncMap(void)
{
	actFuncMap_.emplace(
		"EnemyStateTimeWait",
		[](rapidxml::xml_node<char>* node)
		{
			float waitTime = Str2Val<float>()(node->first_attribute("Time")->value());
			return EnemyStateTimeWait(waitTime);
		}
	);

	actFuncMap_.emplace(
		"EnemyStateSetFunc",
		[](rapidxml::xml_node<char>* node)
		{
			EnemyState state = static_cast<EnemyState>(Str2Val<int>()(node->first_attribute("State")->value()));
			return EnemyStateSetFunc(state);
		}
	);
	actFuncMap_.emplace(
		"MoveFunc",
		[](rapidxml::xml_node<char>* node)
		{
			return MoveFunc();
		}
	);

	actFuncMap_.emplace(
		"RotaFunc",
		[](rapidxml::xml_node<char>* node) {
			return RotaFunc();
		}
	);

	

	actFuncMap_.emplace(
		"NaviWaitSearchFunc",
		[](rapidxml::xml_node<char>* node)
		{
			return NaviWaitSearchFunc();
		}
	);

	actFuncMap_.emplace(
		"NaviSetRoutePatrolFunc",
		[](rapidxml::xml_node<char>* node) 
		{
			return NaviSetRoutePatrolFunc();
		}
	);

	actFuncMap_.emplace(
		"NaviMoveFunc",
		[](rapidxml::xml_node<char>* node)
		{
			return NaviMoveFunc();
		}
	);

	actFuncMap_.emplace(
		"PatrolMoveFunc",
		[](rapidxml::xml_node<char>* node)
		{
			return PatrolMoveFunc();
		}
	);


	actFuncMap_.emplace(
		"PatrolNaviStartFunc",
		[](rapidxml::xml_node<char>* node) {
			return PatrolNaviStartFunc();
		}
	);

	actFuncMap_.emplace(
		"PatrolNaviStopFunc",
		[](rapidxml::xml_node<char>* node) {
			return PatrolNaviStopFunc();
		}
	);

	actFuncMap_.emplace(
		"AnimCorrectMoveVecToAnim",
		[](rapidxml::xml_node<char>* node)
		{
			return AnimCorrectMoveVecToAnim();
		}
	);

	

	actFuncMap_.emplace(
		"EnemyRandRotaFunc",
		[](rapidxml::xml_node<char>* node)
		{
			return EnemyRandRotaFunc();
		}
	);

	
	
}

void BehaviorTreeLoader::CreateCheckFuncMap(void)
{
	ckFuncMap_.emplace(
		"EnemyStateCheckFunc",
		[](rapidxml::xml_node<char>* node)
		{
			EnemyState state = static_cast<EnemyState>(Str2Val<int>()(node->first_attribute("State")->value()));
			return EnemyStateCheckFunc(state);
		}
	);

	ckFuncMap_.emplace(
		"EnemyCheckAngleFunc",
		[](rapidxml::xml_node<char>* node)
		{
			return EnemyCheckAngleFunc();
		}
	);
	

	ckFuncMap_.emplace(
		"NaviCheckDestFunc",
		[](rapidxml::xml_node<char>* node)
		{
			return NaviCheckDestFunc();
		}
	);

	ckFuncMap_.emplace(
		"NaviCheckDestFunc",
		[](rapidxml::xml_node<char>* node)
		{
			return NaviCheckDestFunc();
		}
	);

	ckFuncMap_.emplace(
		"NaviStateCheckFindFunc",
		[](rapidxml::xml_node<char>* node)
		{
			return NaviStateCheckFindFunc();
		}
	);

	ckFuncMap_.emplace(
		"PatrolCheckNotIsStop",
		[](rapidxml::xml_node<char>* node)
		{
			return PatrolCheckNotIsStop();
		}
	);

	ckFuncMap_.emplace(
		"FanColIsHitFunc",
		[](rapidxml::xml_node<char>* node)
		{
			return FanColIsHitFunc();
		}
	);

	ckFuncMap_.emplace(
		"IsMoveFunc",
		[](rapidxml::xml_node<char>* node)
		{
			return IsMoveFunc();
		}
	);

	
	ckFuncMap_.emplace(
		"EnemyIsOverStateTimeFunc",
		[](rapidxml::xml_node<char>* node)
		{
			float limitTime = Str2Val<float>()(node->first_attribute("Time")->value());
			return EnemyIsOverStateTimeFunc(limitTime);
		}
	);


}
