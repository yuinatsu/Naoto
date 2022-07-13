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

	/// <summary> ���W�Ɉ�ԋ߂��G��T�� </summary>
	/// <param name="pos"> ���W </param>
	/// <returns> ��ԋ߂��G </returns>
	Obj& FindEnemy(const Math::Vector2& pos);

	void SortEnemyList(const Math::Vector2& pos);

	Obj& GetPlayer(void);

	// ���j����n��
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

	// ���j��
	int defeats_;

	// ���e�̐���ۑ�����
	int Mines_;

	// �v���C���[
	std::unique_ptr<Obj> player_;

	// �擾���A�C�e��
	std::unique_ptr<Obj> getItem_;

	// �G���X�g
	std::list<std::unique_ptr<Obj>> enemyList_;

	// �M�~�b�N���X�g
	std::list<std::unique_ptr<Obj>> gimicList_;

	// �A�C�e�����X�g
	std::list<std::unique_ptr<Obj>> itemList_;

	// �G�t�F�N�g���X�g
	std::list<std::unique_ptr<Obj>> effectList_;

	std::vector<std::pair<int, std::string>> itemid_;
	
	// ���ݎg�p���ꂽ�A�C�e��
	ItemName useItem_;
	// Math::Vector2 itemPos_;

	std::shared_ptr<GmkEvent> gmkEvent_;
};

