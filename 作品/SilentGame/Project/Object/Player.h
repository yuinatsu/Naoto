#pragma once
#include <map>
#include <list>
#include <sstream>
#include "Unit.h"
#include "state/PlayerState.h"

class Player :
    public Unit
{
public:
    /// <summary> コンストラクタ  </summary>
    /// <param name="cntType"> コントローラ情報 </param>
    /// <param name="pos"> 初期座標 </param>
    Player(CntType cntType, std::shared_ptr<TmxObj> tmx, Math::Vector2 pos);
    ~Player();
private:
    /// <summary> 初期化 </summary>
    /// <param name="cntType"> コントローラーの種類 </param>
    /// <returns> 成功時true失敗時false </returns>
    bool Init(CntType cntType);
    
    /// <summary> 更新 </summary>
    /// <param name="delta"> デルタタイム </param>
    void Update(double delta)override;

    /// <summary> 描画 </summary>
    /// <param name="offset"> 画面オフセット </param>
    void Draw(const Math::Vector2& offset)override;

    void DrawEffect(const Math::Vector2& offset);

    /// <summary> アニメーションイメージ読み込み </summary>
    /// <returns> 成功時true失敗時false </returns>
    bool LoadAnim(void);

    /// <summary> ID取得 </summary>
    /// <returns> ObjID::Player </returns>
    ObjID GetObjID(void) override { return ObjID::Player; };

    /// <summary> プレイヤーアクション </summary>
    std::vector<char> stateVec_;
    rapidxml::xml_document<> stateDoc_;
    rapidxml::xml_node<>* stateNode_;
    animNode* animNode_;
};

