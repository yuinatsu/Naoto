#pragma once
#include "ItemBase.h"
class Weapon :
    public ItemBase
{
public:
    ObjID GetObjID(void) override { return ObjID::Weapon; };      // id�̎擾
};

