#pragma once
#include <Dxlib.h>
#include <map>
#include <vector>
#include <string>
#include <functional>
#include "../Obj.h"
#include "../UI/UiBase.h"
#include "../../Input/InputID.h"
#include "../../Scene/SceneMng.h"
#include "../../common/AnimMng.h"
#include "../../common/rapidxml.hpp"
#include "../../common/rapidxml_utils.hpp"
#include "../../Component/Animation.h"
#include "../../common/Debug.h"
#include "../../common/nameof.hpp"		// 外部データ
#include "../Item.h"


// 移動
struct Move
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string name = atr->name();
			std::string turn = atr->value();
			obj->speed_ = (float)std::atoi(atr->value());
			if (name == "x")
			{
				auto tmp = obj->speed_ * obj->spMag_;
				obj->pos_.x += tmp;
				return true;
			}
			else if (name == "y")
			{
				auto tmp = obj->speed_ * obj->spMag_;
				obj->pos_.y += tmp;
				return true;
			}
		}
		return false;
	}
};


// 攻撃
struct Attack
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string name = atr->name();
			if (name == "power" && obj->atkFlag_)
			{
				obj->atk_ = (float)std::atof(atr->value());
				return true;
			}
		}
		return false;
	}
};


// 移動量変化
struct SpChange
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string name = atr->name();
			if (name == "speed")
			{
				obj->spMag_ = static_cast<float>(std::atof(atr->value()));
				return true;
			}
		}
		return false;
	}
};

// アイテムカーソル
struct ItemCur
{
	bool operator()(UiBase* ui, rapidxml::xml_node<>* node)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string name = atr->name();
			std::string cur = atr->value();
			if (cur == "Left")
			{			
				//// 左回転
				//if (ui->order_.size())
				//{
				//	std::rotate(order_.begin(), order_.begin() + (order_.size() - 1), order_.end());
				//}
				return true;
			}
			else if (cur == "Right")
			{
				//// 右回転
				//if (ui->order_.size())
				//{
				//	std::rotate(order_.begin(), order_.begin() + 1, order_.end());
				//}
				return true;
			}
		}
		return false;
	}
};


// キーチェック
struct CheckKey
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string name = atr->value();
			for (auto tmp : InputID::Max)
			{
				if (name == NAMEOF_ENUM(tmp))
				{
					if (name == "Attack")
					{
						auto tmp = obj->controller_->LongPress(InputID::Attack, 3.0, obj->delta_);
						if (tmp == "LongAttack")
						{
							obj->atkMag_ = 3.0f;
							return true;
						}
						else if (tmp == "Attack")
						{
							obj->atkMag_ = 1.0f;
							return true;
						}				
						return false;
					}
					//else if (name == "ItemLeft" || name == "ItemRight")
					//{
					//	return obj->controller_->Pressed(tmp);
					//}
					else
					{
						// Pressで制御
						return obj->controller_->Press(tmp);
					}
				}
			}
			// その他input情報
			if (name == "Walk")
			{
				// 通常移動（Shift、Ctrlがニュートラル）
				bool rtnflag = false, flag1 = false, flag2 = false;
				for (int n = static_cast<int>(InputID::Up); n <= static_cast<int>(InputID::Right); n++)
				{
					flag1 |= obj->controller_->Press(static_cast<InputID>(n));
				}
				for (int n = static_cast<int>(InputID::Dash); n <= static_cast<int>(InputID::Crouch); n++)
				{
					flag2 |= obj->controller_->Press(static_cast<InputID>(n));
				}
				return (flag1 && !flag2);
			}
			else if (name == "Non")
			{
				// すべてのキーがニュートラル
				bool rtnflag = false;
				for (int n = 0; n < static_cast<int>(InputID::Max); n++)
				{
					rtnflag |= obj->controller_->Press(static_cast<InputID>(n));
				}
				return !rtnflag;
			}
		}
		return false;
	}
};


// アニメーションのセット
struct SetAnime
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string name = atr->name();
			std::string tmp = atr->value();
			if (name == "state")
			{
				dynamic_cast<Animation&>(obj->GetComponent(ComponentID::Animator, "PlayerAnim")).state(tmp);
				if (tmp == "Idle")
				{
					obj->isIdle_ = true;
				}
				else
				{
					obj->isIdle_ = false;
				}
				return true;
			}
		}
		return false;
	}
};


// 当たり判定チェック
struct ColisionCheck
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		Math::Vector2 vec(0, 0);
		Math::Vector2I windowSize = Math::Vector2{1920,1088};
		auto window = [&](Math::Vector2 v)
		{
			return (v >= Math::Vector2{0,0} && v <= Math::Vector2(windowSize));
		};
		Math::Vector2 size;
		float speed = 0;
		auto checkMove = [&](Math::Vector2 moveVec)
		{
			MapCollMng::Ray ray = { { obj->pos_ }, moveVec };
			for (Collision col : obj->tmx_->GetColList())
			{
				if (MapCollMng::CheckCollision(ray, col).first)
				{
					return false;
				}
			}
			for (Collision col2 : obj->tmx_->GetCol2List())
			{
				if (MapCollMng::CheckCollision(ray, col2).first)
				{
					return false;
				}
			}
			return true;
		};

		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string name = atr->name();
			std::string tmp = atr->value();
			if (name == "speed")
			{
				speed = static_cast<float>(atoi(tmp.c_str()));
			}
			if (name == "width")
			{
				vec.x = static_cast<float>(atoi(tmp.c_str()));
				vec.x += speed;
			}
			if (name == "height")
			{
				vec.y = static_cast<float>(atoi(tmp.c_str()));
				vec.y += speed;
			}
			if (name == "attack")
			{
				for (int i = 0; i < 4; i++)
				{
					if (i == 0)
					{
						vec.y = static_cast<float>(atoi(tmp.c_str()));
						vec.y *= -1;
						vec.y -= speed;
					}
					else if (i == 1)
					{
						vec.y = static_cast<float>(atoi(tmp.c_str()));
						vec.y += speed;
					}
					else if (i == 2)
					{
						vec.x = static_cast<float>(atoi(tmp.c_str()));
						vec.x *= -1;
						vec.x -= speed;
					}
					else if (i == 3)
					{
						vec.x = static_cast<float>(atoi(tmp.c_str()));
						vec.x += speed;
					}
					if (!(checkMove(vec) && window(obj->pos_ + vec)))
					{
						return true;
					}
					vec = { 0,0 };
				}
				return false;
			}
		}
		if (checkMove(vec) && window(obj->pos_ + vec))
		{
			return true;
		}
		return false;
	}
};


struct animNode
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node)
	{
		for (auto attach = node->first_node(); attach != nullptr; attach = attach->next_sibling())
		{
			// 名前をとる
			std::string attachName = attach->first_attribute("name")->value();
			// 動きが登録されていたら
			if (animNode_.find(attachName) != animNode_.end())
			{
				// 正しく動作しなかったら次に回る
				if (!animNode_[attachName](obj, attach))
				{
					continue;
				}
				if (!(*this)(obj, attach))
				{
					return false;
				}
			}
		}
		return true;
	}
	std::map<std::string, std::function<bool(Obj* obj, rapidxml::xml_node<>* node)>> animNode_ = {
		{"Move",Move()},
		{"Attack",Attack()},
		{"SpChange",SpChange()},
		{"CheckKey",CheckKey()},
		{"SetAnime",SetAnime()},
		{"ColisionCheck",ColisionCheck()},
	};
};

struct animNodeUI
{
	bool operator()(UiBase* ui, rapidxml::xml_node<>* node)
	{
		for (auto attach = node->first_node(); attach != nullptr; attach = attach->next_sibling())
		{
			// 名前をとる
			std::string attachName = attach->first_attribute("name")->value();
			// 動きが登録されていたら
			if (animNode_.find(attachName) != animNode_.end())
			{
				// 正しく動作しなかったら次に回る
				if (!animNode_[attachName](ui, attach))
				{
					continue;
				}
				if (!(*this)(ui, attach))
				{
					return false;
				}
			}
		}
		return true;
	}
	std::map<std::string, std::function<bool(UiBase* ui, rapidxml::xml_node<>* node)>> animNode_ = {
		{"ItemCur",ItemCur()},
	};
};
