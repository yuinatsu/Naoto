#pragma once
#include <list>
#include "../Obj.h"
#include "../../common/Math.h"

struct Squar;
class ObjManager;
class UiBase;

enum class ItemName;

class Box :
	public Obj
{
public:
	//Alert(CameraMng& cam);
	Box(UiBase& itemUi,const Math::Vector2& pos, ObjManager& objMng, ItemName itemName);
	~Box();
	void Init(void);
	void Update(double delta) override;
	void Draw(const Math::Vector2& drawoffset) override;
	// 箱が空いているかを渡す
	bool GetFlag(void);
private:

	ObjID GetObjID(void) override { return ObjID::Box; }

	// 中に持ち物が入っているか
	bool BelFlag_;

	// 空いているかフラグ
	bool flag_;
	
	// 入っているアイテムの種類
	ItemName itemName_;

	// 発見時の描画輝度の調整
	float sColor_;
	bool scFlag_;

	std::unique_ptr<Squar> squar_;
	
	// オブジェクトマネージャー
	ObjManager& objMng_;

	UiBase& itemUi_;
};

