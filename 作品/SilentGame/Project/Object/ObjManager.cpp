#include <DxLib.h>
#include <fstream>
#include "Player.h"
#include "Enemy.h"
#include "Gimic/SecurityCam.h"
#include "Gimic/Box.h"
#include "Gimic/TrapAlarm.h"
#include "DefeatItem/LaundMine.h"
#include "../Component/Collider/CircleCollider.h"
#include "../common/BehaviorTreeLoader.h"
#include "../Component/BehaviorTree/BehaviorTree.h"
#include "../Component/BehaviorTree/BehaviorBaseNode.h"
#include "../Component/Navi/Navi.h"
#include "ObjManager.h"
#include "Decoy.h"
#include "Alcohol.h"
#include "../common/GmkEvent.h"
#include "../common/nameof.hpp"		// 外部データ

constexpr char sig[4]{ 'd','a','t', 'a'};
constexpr char bname[]{ "Resource/EnemyBehaviorTest.xml" };
constexpr unsigned int version{ 2 };

ObjManager::ObjManager(UiBase& itemUi,std::shared_ptr<GmkEvent>& gmkEvent,std::shared_ptr<TmxObj>& tmxObj) :
	gmkEvent_{gmkEvent}
{
	Load("Resource/obj.data", itemUi, gmkEvent, tmxObj);

	//itemList_.emplace_back(std::make_unique<Decoy>(Math::Vector2{229.0f, 219.0f}));
	//itemList_.emplace_back(std::make_unique<Item>(tmxObj));
	useItem_ = ItemName::Max;
}

ObjManager::~ObjManager()
{
}

bool ObjManager::Update(double delta)
{

	if (!player_.get()->IsAlive() || enemyList_.size() == 0)
	{
		return false;
	}

	player_->Update(delta);

	for (auto& enemy : enemyList_)
	{
		enemy->Update(delta);
	}
	for (auto& gimic : gimicList_)
	{
		gimic->Update(delta);
		if (ObjID::Alert == gimic.get()->GetObjID())
		{
			auto pos = dynamic_cast<Alert*>(gimic.get())->GetSpos();
			if (dynamic_cast<Alert*>(gimic.get())->GetpFlag())
			{
				SortEnemyList(pos);
				gmkEvent_->StartEvent(enemyList_, pos, EventType::Alert);
			}
		}
		
		// 検知されたら
		if (ObjID::TrapAlarm == gimic.get()->GetObjID())
		{
			auto pos = dynamic_cast<TrapAlarm*>(gimic.get())->GetSpos();
			if (dynamic_cast<TrapAlarm*>(gimic.get())->GetpFlag())
			{
				SortEnemyList(pos);
				gmkEvent_->StartEvent(enemyList_, pos, EventType::Alert);
			}
		}
	}
	
	//if (CheckHitKey(KEY_INPUT_SPACE) && Mines_>0)
	//{
	//	Mines_--;
	//	gimicList_.emplace_back(std::make_unique<LaundMine>(player_->GetPos(),enemyList_,player_));
	//}

	for (auto& item : itemList_)
	{
		item->Update(delta);
	}

	switch (useItem_)
	{
	case ItemName::Alcohol:
		itemList_.emplace_back(std::make_unique<Alcohol>(player_->GetPos()));
		break;
	case ItemName::Decoy:
		itemList_.emplace_back(std::make_unique<Decoy>(player_->GetPos()));
		break;
	case ItemName::LaundMine:
		itemList_.emplace_back(std::make_unique<LaundMine>(player_->GetPos(), enemyList_,player_));
		break;
	default:
		break;
	}
	getItem_->Update(delta);
	itemid_ = getItem_->GetItemID();
	

	for (auto& effect : effectList_)
	{
		effect->Update(delta);
	}

	// 当たり判定
	// プレイヤーの当たり判定
	for (auto& pc : player_->GetComponent(ComponentID::Collider))
	{
		// 敵との当たり判定
		for (auto& enemy : enemyList_)
		{
			for (auto& ec : enemy->GetComponent(ComponentID::Collider))
			{
				dynamic_cast<Collider&>(*pc.second).HitCheck(dynamic_cast<Collider&>(*ec.second));
			}
		}
		// ギミックとの当たり判定
		for (auto& gimic : gimicList_)
		{
				// コライダーを持っているかチェック
			if (gimic->IncludeComponent(ComponentID::Collider))
			{
				// 持っているコライダーとの当たり判定をとる
				for (auto& gc : gimic->GetComponent(ComponentID::Collider))
				{
					dynamic_cast<Collider&>(*pc.second).HitExCheck(dynamic_cast<Collider&>(*gc.second));
				}
			}
		}
	}
	// 設置物と敵の判定
	for (auto& item : itemList_)
	{
		for (auto& enemy : enemyList_)
		{
			if (!item->IncludeComponent(ComponentID::Collider))
			{
				continue;
			}
			for (auto& ic : item->GetComponent(ComponentID::Collider))
			{
				for (auto& ec : enemy->GetComponent(ComponentID::Collider))
				{
					dynamic_cast<Collider&>(*ic.second).HitCheck(dynamic_cast<Collider&>(*ec.second));
				}
			}
		}
	}

	// 爆弾と敵の当たり判定
	//for (auto& gimic : gimicList_)
	//{
	//	if (ObjID::LandMine == (*gimic).GetObjID())
	//	{
	//		for (auto& gc : gimic->GetComponent(ComponentID::Collider))
	//		{
	//			for (auto& enemy : enemyList_)
	//			{
	//				for (auto& ec : enemy->GetComponent(ComponentID::Collider))
	//				{
	//					dynamic_cast<Collider&>(*gc.second).HitCheck(dynamic_cast<Collider&>(*ec.second));
	//				}
	//			}
	//		}
	//	}
	//}

	// 死亡したキャラを破棄する(削除した数を撃破数として加算)
	defeats_ += static_cast<int>(enemyList_.remove_if([](std::unique_ptr<Obj>& obj) {return (*obj).IsAlive() == false; }));
	// 使用したアイテムを破棄する
	itemList_.remove_if([](std::unique_ptr<Obj>& obj) {return (*obj).IsAlive() == false; });

	return true;

}

void ObjManager::Draw(const Math::Vector2& offset)
{
	player_->Draw(offset);
	
	for (auto& enemy : enemyList_)
	{
		enemy->Draw(offset);
	}

	for (auto& gimic : gimicList_)
	{
		gimic->Draw(offset);
	}

	for (auto& item : itemList_)
	{
		item->Draw(offset);
	}

	getItem_->Draw(offset);

	for (auto& effect : effectList_)
	{
		effect->Draw(offset);
	}
}

Obj& ObjManager::FindEnemy(const Math::Vector2& pos)
{
	enemyList_.sort([&pos](std::unique_ptr<Obj>& objA, std::unique_ptr<Obj>& objB) {
		
		return (objA->GetPos() - pos).SqMagnitude() < (objB->GetPos() - pos).SqMagnitude();
		}
	);
	return **enemyList_.begin();
}

void ObjManager::SortEnemyList(const Math::Vector2& pos)
{
	enemyList_.sort([&pos](std::unique_ptr<Obj>& objA, std::unique_ptr<Obj>& objB) {

		return (objA->GetPos() - pos).SqMagnitude() < (objB->GetPos() - pos).SqMagnitude();
		}
	);
}

Obj& ObjManager::GetPlayer(void)
{
	return *player_;
}

int ObjManager::GetDefeats(void)
{
	return defeats_;
}


int ObjManager::GetMines(void)
{
	return Mines_;
}

bool ObjManager::AddItem(std::unique_ptr<Obj>&& item)
{
	return false;
}

bool ObjManager::Load(const std::string& xmlName, UiBase& itemUi, std::shared_ptr<GmkEvent>& gmkEvent, std::shared_ptr<TmxObj>& tmxObj)
{
	// 配置データを読み込む
	std::ifstream ifs("Resource/obj.data", std::ios::binary);

	// ファイルオープンしたかチェック
	if (!ifs)
	{
		// してないとき処理をやめる
		return false;
	}

	// ファイルヘッダー
	Header h;

	// ヘッダー部を読み込む
	ifs.read(reinterpret_cast<char*>(&h), sizeof(h));

	if (h.ver != version)
	{
		DebugLog("このバージョンに対応していません");
		return false;
	}

	// シグネチャをチェック
	for (int i = 0; i < 4; i++)
	{
		if (h.s[i] != sig[i])
		{
			return false;
		}
	}

	// ビヘイビアツリーを読み込む
	std::unique_ptr<BehaviorTreeLoader> bloader = std::make_unique<BehaviorTreeLoader>();

	const std::unordered_map<ObjID, std::function<void(ObjData&, std::ifstream&)>> func{
		{ObjID::Player, [this,&tmxObj](ObjData& objData, std::ifstream& f) {
			CreatePlayer(tmxObj,objData,f);
		}},
		{ObjID::Enemy,[this,&tmxObj,&bloader](ObjData& objData, std::ifstream& f) {
			CreateEnemy(*bloader,tmxObj,objData,f);
		}},
		{ObjID::Box, [this,&tmxObj,&itemUi](ObjData& objData, std::ifstream& f) {
			// ボックスを生成する
			int item = 0;		// アイテムの種類
			f.read(reinterpret_cast<char*>(&item), sizeof(item));
			// ここに生成を書く
			auto& g = gimicList_.emplace_back(std::make_unique<Box>(itemUi,objData.pos_, *this, static_cast<ItemName>(item)));
			g->AddComponent(std::make_unique<CircleCollider>(15.0f, [](Collider& obj) {}, "BoxCol", *g));
		}},
		{ObjID::Alert, [this,&tmxObj](ObjData& objData, std::ifstream& f) {
			// セキュリティカメラ
			// objData.posに座標 objData.vecにベクトルが入ってる
			gimicList_.emplace_back(std::make_unique<Alert>(objData.pos_,objData.vec_,tmxObj,player_));
		}},
		{ObjID::TrapAlarm, [this,&tmxObj](ObjData& objData, std::ifstream& f) {
		}}
	};
	//gimicList_.emplace_back(std::make_unique<LaundMine>());
	auto& g = gimicList_.emplace_back(std::make_unique<TrapAlarm>(Math::Vector2{ 950,270 }, *this));
	g->AddComponent(std::make_unique<CircleCollider>(15.0f, [](Collider& other) {}, "BoxCol", *g));
	getItem_ = std::make_unique<Item>(tmxObj);
	// データのヘッダー情報
	DateHeader dh;

	// 読み込む
	ifs.read(reinterpret_cast<char*>(&dh), sizeof(dh));

	// ファイルがEOFの位置までループ
	while (!ifs.eof())
	{
		// データの個数分for文を回す
		for (int i = 0; i < dh.num; i++)
		{
			// オブジェクト用のデータを読む
			ObjData objData;
			int strSize;
			ifs.read(reinterpret_cast<char*>(&objData.pos_), sizeof(objData.pos_));
			ifs.read(reinterpret_cast<char*>(&objData.vec_), sizeof(objData.vec_));
			ifs.read(reinterpret_cast<char*>(&objData.no_), sizeof(objData.no_));
			ifs.read(reinterpret_cast<char*>(&strSize), sizeof(strSize));
			objData.imgName_.resize(strSize);
			ifs.read(reinterpret_cast<char*>(objData.imgName_.data()), sizeof(objData.imgName_[0]) * strSize);

			// 種類に合わせてオブジェクトを生成する
			func.at(dh.id)(objData, ifs);
		}
		ifs.read(reinterpret_cast<char*>(&dh), sizeof(dh));
	}
	return true;
}

void ObjManager::CreatePlayer(std::shared_ptr<TmxObj>& tmxObj,ObjManager::ObjData& obj, std::ifstream& f)
{
	// コントローラー情報
	if (GetJoypadNum())
	{
		player_ = std::make_unique<Player>(CntType::Pad, tmxObj, obj.pos_);
	}
	else
	{
		player_ = std::make_unique<Player>(CntType::Key, tmxObj, obj.pos_);
	}
	player_->AddComponent(std::make_unique<CircleCollider>(12.0f, [](Collider& other) {}, "BodyCol", *player_));
	player_->AddComponent(std::make_unique<CircleCollider>(24.0f, [this](Collider& other) {
		if (useItem_ == ItemName::Knife && other.GetName() == "BodyCol")
		{
			other.GetOwner().Destroy();
			player_->SetAtkFlag(true);
		}
		}, "AttackCol", *player_));
}

void ObjManager::CreateEnemy(BehaviorTreeLoader& bloder, std::shared_ptr<TmxObj>& tmxObj, ObjData& obj, std::ifstream& f)
{
	int num;
	std::vector<Math::Vector2I> route;
	// 巡回ルート読み込み
	f.read(reinterpret_cast<char*>(&num), sizeof(num));
	route.resize(num);
	f.read(reinterpret_cast<char*>(route.data()), sizeof(route[0]) * num);

	// ビヘイビアツリーのデータのファイル名を読み込み
	std::string xmlName;
	f.read(reinterpret_cast<char*>(&num), sizeof(num));
	xmlName.resize(num);
	f.read(reinterpret_cast<char*>(xmlName.data()), sizeof(xmlName[0]) * num);
	auto& e = enemyList_.emplace_back(std::make_unique<Enemy>(route, tmxObj, obj.pos_));

	// コンポーネント追加
	e->AddComponent(std::make_unique<BehaviorTree>(std::move(bloder.Load(xmlName)), "EnemyBehavior", *e));
}
