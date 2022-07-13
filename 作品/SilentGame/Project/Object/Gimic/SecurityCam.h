#pragma once
#include <list>
#include "../../common/MapCollMng.h"
#include "../../common/Math.h"
#include "../../Resource/Tmx/TmxObj.h"
#include "../../common/Camera/CameraMng.h"
#include "../../common/Structure.h"
#include "../../common/Time.h"
#include "../Obj.h"

using Vector2 = Math::Vector2;

class Alert:
	public Obj
{
public:
	Alert(Vector2 pos,Vector2 vec, std::shared_ptr<TmxObj>& tmxObj, std::unique_ptr<Obj>& player);
	~Alert();
	void Init(void);
	void Update(double delta) override;
	// プレイヤーを見つけていないときの処理
	void UpdateNoDis(const Vector2& pos, float delta);
	// プレイヤーを見つけた時の処理
	void UpdateDis(const Vector2& pos, float delta);
	void Draw(const Math::Vector2& offset) override;
	ObjID GetObjID(void) { return ObjID::Alert; };
	// 見つけた時の座標を渡す
	Vector2 GetSpos(void);
	// プレイヤーを検知したかどうかを受け取る
	bool GetpFlag(void);

private:
	// プレイヤーが見つかった時の座標を受け取る
	void SetPos(const Vector2& pos);
	// マップ情報を受け取る
	std::shared_ptr<TmxObj>& tmxObj_;
	// プレイヤーの情報を受け取る
	std::unique_ptr<Obj>& player_;

	// 視線の回転を逆回転に
	bool rotFlag_;
	// 視線の回転を反転するまでの時間
	float rotTime_;
	// プレイヤーが入ったどうか
	bool pflag_;

	std::unique_ptr<Fan> fan_;
	Vector2 pos_;
	// プレイヤーがどれかの視線に入ったかどうか
	bool sFlag_;
	// プレイヤーを見つけて何秒立ったのか
	float Time_;
	// プレイヤーが見つかった時の座標を入れる
	Vector2 sPos_;
};

