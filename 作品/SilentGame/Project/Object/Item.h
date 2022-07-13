#pragma once
#include <map>
#include <list>
#include <sstream>
#include <vector>
#include "ItemBase.h"

using ItemData = std::pair<int, int>;
using ItemVecData = std::vector<Math::Vector2>;

enum class ItemName 
{
    Knife,          // ナイフ
    Decoy,          // デコイ
    Alcohol,        // お酒
    LaundMine,      // 地雷
    Max
};


class Item :
    public ItemBase
{
public:
    Item(std::shared_ptr<TmxObj> tmx);
    ~Item();
private:
    bool Init();
    void Update(double delta);
    void Draw(const Math::Vector2& offset);
    bool LoadAnim(std::pair<int, std::string> itemid);
    bool LoadData(std::string fileName);
    ObjID GetObjID(void) override { return ObjID::Item; };      // idの取得

    rapidxml::xml_document<> tsxDoc_;
    rapidxml::xml_node<>* stateNode_;
    std::string map_;
};

