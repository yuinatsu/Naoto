#pragma once
#include "../Obj.h"
class ObjManager;


using EnemyList = std::list<std::unique_ptr<Obj>>;

class LaundMine :
    public Obj
{
public:
    LaundMine(const Vector2& pos, EnemyList& enemyList, std::unique_ptr<Obj>& player);
    ~LaundMine();

    void Init(void);
    void Update(double delta) override;
    void Draw(const Math::Vector2& drawoffset) override;
private:
    std::unique_ptr<Obj>& player_;
    EnemyList& enemyList_;            // エネミーの情報
    Vector2 bonbpos_;               // 爆弾の座標

    float time_;

    ObjID GetObjID(void) override { return ObjID::LandMine; };
};

