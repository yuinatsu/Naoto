#pragma once
#include <memory>
#include <list>
#include "BaseScene.h"
#include "../Object/Gimic/SecurityCam.h"
#include "../Object/Gimic/Box.h"
#include "../Object/Obj.h"
#include "../common/GmkEvent.h"
#include "../Resource/Tmx/TmxObj.h"
#include "../common/Camera/CameraMng.h"
#include "../Object/UI/UiBase.h"

class ObjManager;

class GameScene :
    public BaseScene
{
public:
    GameScene();
    ~GameScene();
private:
    bool Init(void) override;
    uniqueScene Update(float delta, uniqueScene ownScene) override;
    void DrawOwnScreen(float delta) override;  // 自分自身を描画
    Scene GetSceneID(void) override { return Scene::Game; };    // 自分はゲームシーン
    bool GetFlag(void) override { return SceneFlag_; };
    // オブジェクトを管理するクラス
    std::unique_ptr<ObjManager> objMng_;

    std::list<std::shared_ptr<UiBase>> uiList_;

    CameraMng Cammng_;
    std::shared_ptr<GmkEvent> gEvent_;
    
    // 経過時間計測
    float elTime_;
    // 撃破数
    int defeats_;

    // マップをロードするため
    std::string map_;
    std::shared_ptr<TmxObj> tmxObj_;
    std::vector<char> stateVec_;
    rapidxml::xml_node<>* stateNode_;
    rapidxml::xml_document<> stateDoc_;
    Math::Vector2I ViewSize_;
    int viewID_;

    bool isFirst_;

};

