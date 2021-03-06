#include <DxLib.h>
#include "TransitionScene.h"
#include "../../_debug/_DebugConOut.h"


TransitionScene::TransitionScene(uniqueBaseScene beforScene, uniqueBaseScene afterScene)
{
	beforScene_ = std::move(beforScene);
	afterScene_ = std::move(afterScene);
	//TRACE("TransitionSceneの生成\n");
	DrawOwnScreen();
}


TransitionScene::~TransitionScene()
{

}


uniqueBaseScene TransitionScene::Update(uniqueBaseScene own)
{
	if (UpdateTransition())
	{
		//TRACE("TransitionSceneの終了\n");
		return std::move(afterScene_);
	}
	return own;
}


SceneID TransitionScene::GetSceneID()
{
	return SceneID::TRANSITION;
}


bool TransitionScene::Init()
{
	return true;
}
