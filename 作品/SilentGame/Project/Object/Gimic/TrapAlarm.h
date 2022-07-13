#pragma once
#include <list>
#include "../Obj.h"
#include "../../common/Math.h"

struct Squar;
class ObjManager;

class TrapAlarm :
    public Obj
{
public:
    TrapAlarm(const Math::Vector2& pos, ObjManager& objMng);
    ~TrapAlarm();
    void Init(void);
    void Update(double delta) override;
    void Draw(const Math::Vector2& offset) override;
    // 見つけた時の座標を渡す
    Math::Vector2 GetSpos(void);
    // プレイヤーを検知したかどうかを受け取る
    bool GetpFlag(void);
private:
    ObjID GetObjID(void) override { return ObjID::TrapAlarm; };
    std::unique_ptr<Squar> squar_;
    ObjManager& objMng_;
    bool flag_;
    float sTime_;
    // 空いた瞬間のプレイヤーの位置
    Math::Vector2 sPos_;
    // プレイヤーが入ったどうか
    bool pflag_;
};

