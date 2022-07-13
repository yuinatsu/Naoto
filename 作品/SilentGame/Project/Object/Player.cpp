#include "Player.h"
#include "../Input/Keyboard.h"
#include "../Input/Pad.h"
#include "../common/rapidxml.hpp"
#include "../common/rapidxml_utils.hpp"
#include "../common/AnimMng.h"
#include "../Component/Animation.h"
#include "../common/ImageMng.h"
#include "../common/Debug.h"

// �A�j���[�V�����Q�Ɨp
constexpr char AnimCompName[]{ "PlayerAnim" };

Player::Player(CntType cntType, std::shared_ptr<TmxObj> tmx, Math::Vector2 pos)
{
	// ������
	tmx_ = tmx;
	pos_ = pos;
	Init(cntType);
}

Player::~Player()
{
	delete animNode_;
}

bool Player::Init(CntType cntType)
{
	// �v���C���[�̃C���[�W�ƃA�j���[�V�����ǂݍ���
	if (!LoadAnim())
	{
		return false;
	}		

	// �R���g���[�����
	if (cntType == CntType::Key)
	{
		// �L�[�{�[�h
		controller_ = std::make_unique<Keyboard>();
	}
	if (cntType == CntType::Pad)
	{
		// �Q�[���p�b�h
		controller_ = std::make_unique<Pad>();
	}

	// �v���C���[�A�N�V�����ǂݍ���
	rapidxml::file<> attach = "Resource/Xml/PlayerAction.tsx";
	stateVec_ = attach.vecData();
	stateDoc_.parse<0>(stateVec_.data());
	stateNode_ = stateDoc_.first_node("objectList");
	animNode_ = new animNode();

	// Effect
	lpImageMng.GetID("Resource/Image/Effect/slash.png", "effect", Math::Vector2{ 64,64 }, { 9,1 });

	return true;
}

void Player::Update(double delta)
{
	delta_ = delta;
	// �L�[����
	if (!(*controller_)(delta))
	{
		// �R���g���[����񂪖���������͂���
		return;
	}
	// �v���C���[�̍s������
	for (auto node = stateNode_->first_node(); node != nullptr; node = node->next_sibling())
	{
		animNode()(this, node);
	}
	// �A�j���[�V�����X�V
	UpdateComponent(delta);
	// �R���g���[���[�X�V
	controller_->Update(delta);
}

void Player::Draw(const Math::Vector2& offset)
{
	// Vector2 check(colPos_);
	// �v���C���[�\��
	dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, AnimCompName)).Draw(pos_ + offset, size_, isIdle_);
	DrawEffect(offset);
}

void Player::DrawEffect(const Math::Vector2& offset)
{
	if (atkFlag_)
	{
		int n = 8;
		for (int i = 0; i < (n * 1); i++)
		{
			DrawGraph(pos_.x + offset.x - 30, pos_.y + offset.y - 30, lpImageMng.GetID("effect")[(i / 1) + 1], true);                       // �L�����`�b�v
		}
		atkFlag_ = false;
	}
}

bool Player::LoadAnim(void)
{
	bool rtnflag = true;
	// �Ԃ�l��Flag�`�F�b�N
	auto check = [&rtnflag](bool flag)
	{
		// ��ł��U������ΕԂ�l��false
		rtnflag &= flag;
	};
	// �A�j���[�V�����̎��
	std::array<std::string, 4> list = { "Down","Left","Right","Up" };

	// �A�j���[�V�����N���X�ǉ�
	AddComponent(std::make_unique<Animation>("Player", AnimCompName, *this));
	// �A�j���[�V�����N���X�擾
	auto& anim = dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, AnimCompName));
	// �O������xml���擾��SetXml�Ɋi�[
	check(lpAnimMng.SetXml(anim.GetKey(), "Resource/Xml/PlayerImage.tsx"));
	for (auto& data : list)
	{
		check(lpAnimMng.SetItem(anim.GetKey(), data));
	}
	// �A�j���[�V����������
	anim.state("Down");
	// �v���C���[�T�C�Y�擾
	size_ = lpAnimMng.GetImageSize(anim.GetKey());
	return rtnflag;
}
