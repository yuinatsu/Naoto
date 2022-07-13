#pragma once
#include <memory>
#include <list>
#include <vector>
#include "../Object/Obj.h"
#include "../common/Math.h"
#include "Item.h"

// class Obj;
class TmxObj;
class GmkEvent;
class UiBase;
class BehaviorTreeLoader;

class ObjManager
{
public:
	ObjManager(UiBase& itemUi,std::shared_ptr<GmkEvent>& gmkEvent,std::shared_ptr<TmxObj>& tmxObj);
	~ObjManager();

	bool Update(double delta);
	void Draw(const Math::Vector2& offset);

	/// <summary> 座標に一番近い敵を探す </summary>
	/// <param name="pos"> 座標 </param>
	/// <returns> 一番近い敵 </returns>
	Obj& FindEnemy(const Math::Vector2& pos);

	void SortEnemyList(const Math::Vector2& pos);

	Obj& GetPlayer(void);

	// 撃破数を渡す
	int GetDefeats(void);
	

	int GetMines(void);

	bool AddItem(std::unique_ptr<Obj>&& item);

	std::vector<std::pair<int, std::string>> GetItemID(void) { return itemid_; };
	void SetUseItem(ItemName item) { useItem_ = item; };
private:

	bool Load(const std::string& xmlName,UiBase& itemUi, std::shared_ptr<GmkEvent>& gmkEvent, std::shared_ptr<TmxObj>& tmxObj);

	

	struct Header
	{
		char s[4];
		unsigned int ver;
		unsigned int sum;
	};

	struct DateHeader
	{
		ObjID id;
		int num;
	};

	struct ObjData
	{
		Math::Vector2 pos_;
		Math::Vector2 vec_;
		int no_;
		std::string imgName_;
	};

	void CreatePlayer(std::shared_ptr<TmxObj>& tmxObj,ObjData& obj, std::ifstream& f);
	void CreateEnemy(BehaviorTreeLoader& bloder,std::shared_ptr<TmxObj>& tmxObj, ObjData& obj, std::ifstream& f);

	// 撃破数
	int defeats_;

	// 爆弾の数を保存する
	int Mines_;

	// プレイヤー
	std::unique_ptr<Obj> player_;

	// 取得中アイテム
	std::unique_ptr<Obj> getItem_;

	// 敵リスト
	std::list<std::unique_ptr<Obj>> enemyList_;

	// ギミックリスト
	std::list<std::unique_ptr<Obj>> gimicList_;

	// アイテムリスト
	std::list<std::unique_ptr<Obj>> itemList_;

	// エフェクトリスト
	std::list<std::unique_ptr<Obj>> effectList_;

	std::vector<std::pair<int, std::string>> itemid_;
	
	// 現在使用されたアイテム
	ItemName useItem_;
	// Math::Vector2 itemPos_;

	std::shared_ptr<GmkEvent> gmkEvent_;
};

