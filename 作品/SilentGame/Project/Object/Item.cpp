#include "Item.h"
#include "../Component/Animation.h"
#include "../common/AnimMng.h"
#include "../common/nameof.hpp"		// �O���f�[�^
#include "../common/Debug.h"

constexpr char AnimCompName[]{ "ItemAnim" };

Item::Item(std::shared_ptr<TmxObj> tmx)
{
	tmx_ = tmx;
	map_ = "map1";
	Init();
}

Item::~Item()
{
}

bool Item::Init()
{
	if (!LoadData("Resource/Xml/ItemData.tsx"))
	{
		return false;
	}
	for (auto& load : itemId_)
	{
		if (!LoadAnim(load))
		{
			return false;
		}
	}
	return true;
}

void Item::Update(double delta)
{
	delta_ = delta;
	UpdateComponent(delta);
}

void Item::Draw(const Math::Vector2& offset)
{
	//int cnt = 0;
	//for (auto& data : itemData_)
	//{
	//	for (auto& pos : data.second)
	//	{
	//		dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, AnimCompName)).Draw(Math::Vector2{ (float)pos.x, (float)pos.y } + offset, size_, itemId_[cnt].second);
	//	}
	//	cnt++;
	//}
}

bool Item::LoadAnim(std::pair<int, std::string> itemid)
{
	bool rtnflag = true;
	// �Ԃ�l��Flag�`�F�b�N
	auto check = [&rtnflag](bool flag)
	{
		// ��ł��U������ΕԂ�l��false
		rtnflag &= flag;
	};
	// �A�j���[�V�����̎��
	std::array<std::string, 2> list = { "Decoy","Alcohol" };

	// �A�j���[�V�����N���X�ǉ�
	AddComponent(std::make_unique<Animation>("Item", AnimCompName, itemid, *this));
	// �A�j���[�V�����N���X�擾
	auto& anim = dynamic_cast<Animation&>(GetComponent(ComponentID::Animator, AnimCompName));
	// �O������xml���擾��SetXml�Ɋi�[
	check(lpAnimMng.SetXml(anim.GetKey(), "Resource/Xml/ItemImage.tsx"));
	for (auto& data : list)
	{
		check(lpAnimMng.SetItem(anim.GetKey(), data));
	}
	// �A�j���[�V����������
	anim.state(itemid.second);
	// �v���C���[�T�C�Y�擾
	size_ = lpAnimMng.GetImageSize(anim.GetKey());
	return rtnflag;
}

bool Item::LoadData(std::string fileName)
{
	rapidxml::file<> xmlFile = fileName.c_str();
	tsxDoc_.parse<0>(xmlFile.data());

	auto data = tsxDoc_.first_node();
	if (data != nullptr)
	{
		for (auto map = data->first_node("map"); map != nullptr; map = map->next_sibling())
		{
			bool isMap = false;
			if (map)
			{
				for (auto atr = map->first_attribute(); atr != nullptr; atr = atr->next_attribute())
				{
					std::string name = atr->name();
					if (name == "name")
					{
						if (map_ == atr->value())
						{
							isMap = true;
						}
					}
				}
			}
			std::string itemName;
			int id;
			if (isMap)
			{
				for (auto item = map->first_node("item"); item != nullptr; item = item->next_sibling())
				{
					if (item)
					{
						for (auto atr = item->first_attribute(); atr != nullptr; atr = atr->next_attribute())
						{
							std::string name = atr->name();
							if (name == "name")
							{
								itemName = atr->value();
							}
							if (name == "id")
							{
								id = std::atoi(atr->value());
							}
						}
					}
					itemId_.push_back(std::make_pair(id, itemName));
				}
			}
		}
	}
	return true;
}
