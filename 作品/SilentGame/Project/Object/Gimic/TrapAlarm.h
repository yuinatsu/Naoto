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
    // ���������̍��W��n��
    Math::Vector2 GetSpos(void);
    // �v���C���[�����m�������ǂ������󂯎��
    bool GetpFlag(void);
private:
    ObjID GetObjID(void) override { return ObjID::TrapAlarm; };
    std::unique_ptr<Squar> squar_;
    ObjManager& objMng_;
    bool flag_;
    float sTime_;
    // �󂢂��u�Ԃ̃v���C���[�̈ʒu
    Math::Vector2 sPos_;
    // �v���C���[���������ǂ���
    bool pflag_;
};

