#pragma once
#include "UiBase.h"
#include "../../Input/Controller.h"
#include "../state/PlayerState.h"

constexpr int haveItemMax = 6;

class ItemUi :
    public UiBase
{
public:
    ItemUi(const Math::Vector2& pos, const Math::Vector2& scrSize);
    ~ItemUi();
    void Update(const double& delta) override;
    void ItemUpdate(const double& delta)override;
    void UIDraw(const double& delta) override;
    void ItemDraw(const Math::Vector2& pos);
    bool SetItemID(std::pair<int, std::string> id)override;
    ItemName GetUseItem()override;
    std::vector<std::pair<int, std::string>> GetItemID()override { return id_; };
private:
    int mask_;
    ItemName useItem_;
    Math::Vector2 size_;
    std::vector<std::pair<int, std::string>> id_;       // pair<ID, �A�C�e����>
    std::vector<std::pair<int, bool>> order_;           // pair<�A�C�e��ID, �擪���ǂ���>
    /// <summary> �v���C���[�A�N�V���� </summary>
    std::vector<char> stateVec_;
    rapidxml::xml_document<> stateDoc_;
    rapidxml::xml_node<>* stateNode_;
    animNodeUI* animNodeUI_;
};

