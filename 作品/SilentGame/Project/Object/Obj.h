#pragma once
#include <memory>
#include <unordered_map>
#include "../Component/ComponentID.h"
#include "../common/Math.h"
#include "../input/Controller.h"
#include "../Resource/Tmx/TmxObj.h"
#include "../common/MapCollMng.h"
#include "../Component/Animation.h"
#include <string>


class Component;

using ComponentUPTr = std::unique_ptr<Component>;
using ComponentMap = std::unordered_map<ComponentID,std::unordered_map<std::string_view, ComponentUPTr>>;

// state
struct Move;
struct Attack;
struct SpChange;
struct CheckKey;
struct SetAnime;
struct ColisionCheck;

enum class ObjID
{
	Player,
	Enemy,
	Item,
	Weapon,
	UI,
	Box,
	Alert,
	TrapAlarm,
	LandMine,
	Alcohol,
	Decoy
};

class Obj
{
public:
	Obj();
	virtual ~Obj();

	virtual void Update(double delta);
	//virtual void Draw(void) const;
	virtual void Draw(const Math::Vector2& offset);

	/// <summary> コンポーネントを取得する </summary>
	/// <param name="id"> 取得したいコンポーネントのID </param>
	/// <returns> コンポーネントの参照 </returns>
	const std::unordered_map<std::string_view, ComponentUPTr>& GetComponent(ComponentID id) const;

	/// <summary> コンポーネントを取得する </summary>
	/// <param name="id"> 取得したいコンポーネントのID </param>
	/// <returns> コンポーネントの参照 </returns>
	Component& GetComponent(ComponentID id,std::string_view name) const;

	/// <summary> IDに該当するコンポーネントが含まれるか </summary>
	/// <param name="id"> 探したいコンポーネントのID </param>
	/// <returns></returns>
	bool IncludeComponent(ComponentID id) const;

	/// <summary> IDに該当するコンポーネントが含まれるか </summary>
	/// <param name="id"> 探したいコンポーネントのID </param>
	/// <returns></returns>
	bool IncludeComponent(ComponentID id, std::string_view name) const;

	/// <summary> コンポーネントを追加する </summary>
	/// <param name="component"> 追加したいコンポーネント </param>
	/// <returns> 成功時true失敗時false </returns>
	bool AddComponent(ComponentUPTr&& component);

	/// <summary> コンポーネントを削除する </summary>
	/// <param name="id"> 削除したいコンポーネント </param>
	/// <returns> 成功時true失敗時false </returns>
	bool RemoveComponent(ComponentID id,std::string_view name);


	/// <summary> 座標を取得 </summary>
	/// <param name=""></param>
	/// <returns> 座標 </returns>
	const Math::Vector2& GetPos(void) const;

	/// <summary> 座標をセット </summary>
	/// <param name="pos"> セットしたい座標 </param>
	void SetPos(const Math::Vector2& pos);

	
	virtual ObjID GetObjID(void) = 0;

	/// <summary> 移動方向ベクトルをセットする </summary>
	/// <param name="moveVec"></param>
	void SetMoveVec(const Math::Vector2& moveVec);

	/// <summary> 移動方向ベクトルを取得する </summary>
	/// <param name=""></param>
	/// <returns> 移動方向ベクトル </returns>
	const Math::Vector2& GetMoveVec(void) const;

	/// <summary> moveVec、speed_、spMag_、deltaを使い移動する </summary>
	/// <param name="delta"></param>
	virtual void MovePos(double delta);

	/// <summary> 移動できるかどうか？ </summary>
	/// <param name=""></param>
	/// <returns> 移動できるときtrueできないときfalse </returns>
	bool IsMove(void);

	/// <summary> スピードを取得する </summary>
	/// <param name=""> スピード </param>
	/// <returns></returns>
	const float GetSpeed(void) const;

	/// <summary> スピードの倍率を取得する </summary>
	/// <param name=""></param>
	/// <returns> スピードの倍率 </returns>
	const float GeSpMag(void) const;

	/// <summary> アイドル状態フラグをセットする </summary>
	/// <param name="flag"> セットするフラグ </param>
	void SetIdleFlag(bool flag) { isIdle_ = flag; }

	/// <summary> アイドル状態か？ </summary>
	/// <param name=""></param>
	/// <returns> アイドル状態の時trueそうでないときfalse </returns>
	const bool IsIdle(void)const { return isIdle_; }

	/// <summary> 生存しているか？ </summary>
	/// <param name=""></param>
	/// <returns> 生存しているときtrueしていないときfalse </returns>
	const bool IsAlive(void) const { return alive_; }

	/// <summary> このオブジェクトを破棄するために生存フラグをfalseにする </summary>
	/// <param name=""></param>
	void Destroy(void) { alive_ = false; }
	std::vector<std::pair<int, std::string>> GetItemID(void) { return itemId_; };

	void SetAtkFlag(bool flag) { atkFlag_ = flag; };
protected:

	/// <summary> コンポーネントの更新処理 </summary>
	/// <param name="delta"></param>
	void UpdateComponent(double delta) const;

	/// <summary> 座標 </summary>
	Math::Vector2 pos_;

	/// <summary> サイズ </summary>
	Math::Vector2 size_;

	/// <summary> 移動方向 </summary>
	Math::Vector2 moveVec_;

	/// <summary> 移動量 </summary>
	float speed_;

	/// <summary> 移動量倍率 </summary>
	float spMag_;

	/// <summary> 攻撃力 </summary>
	float atk_;

	/// <summary> 攻撃力倍率 </summary>
	float atkMag_;

	/// <summary> 攻撃実行フラグ </summary>
	float atkFlag_;

	/// <summary> コントローラ情報 </summary>
	std::unique_ptr<Controller> controller_;

	/// <summary> デルタタイム </summary>
	double delta_;

	bool isIdle_;

	// 生存フラグ
	bool alive_;

	bool isItemUse_;

	//Math::Vector2 colPos_;												// 当たり判定の中心座標
	//std::map<std::string, std::list<Math::Vector2>> colVec_;				// 当たり判定の方向
	
	//MapCollMng raycast_;

	std::vector<std::pair<int, std::string>> itemId_;

	std::shared_ptr<TmxObj> tmx_;

	// friend
	friend Move;
	friend Attack;
	friend SpChange;
	friend CheckKey;
	friend SetAnime;
	friend ColisionCheck;
private:

	/// <summary> コンポーネント類をマップで持つ </summary>
	ComponentMap componentList_;
};

