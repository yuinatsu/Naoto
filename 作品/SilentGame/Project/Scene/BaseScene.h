#pragma once
#include<memory>
#include"../common/Math.h"
#include "../Input/Controller.h"

class BaseScene;
// usingで短く
using uniqueScene = std::unique_ptr<BaseScene>;

enum class Scene
{
	Transtion,
	Title,
	Select,
	Game,
	Pause,
	ResultScene,
	Max
};

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual bool Init(void) = 0;
	virtual uniqueScene Update(float delta, uniqueScene ownScene) = 0;
	virtual void Draw(float delta);
	virtual void DrawOwnScreen(float delta) = 0;
	virtual Scene GetSceneID(void) = 0;		// 今どのシーンなのか
	virtual bool GetFlag(void) = 0;
private:

protected:
	bool SceneFlag_;
	Math::Vector2I screenSize_;
	int screenID_;		// データの格納
	std::unique_ptr<Controller> controller_;		// コントローラ情報
	int mapNum_;
};

