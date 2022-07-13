#include <DxLib.h>
#include "TransitionScene.h"

TransitionScene::TransitionScene(uniqueScene beforScene, uniqueScene afterScene)
{
	// ��̃V�[���̕ۑ�
	beforScene_ = std::move(beforScene);
	afterScene_ = std::move(afterScene);
	count = 0;
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	beforScene_->Draw(0);
	SceneFlag_ = false;
}

TransitionScene::~TransitionScene()
{
}

bool TransitionScene::Init(void)
{
	return false;
}

uniqueScene TransitionScene::Update(float delta, uniqueScene ownScene)
{
	// 3�b�o�����玟�̃V�[���ֈȍ~
	if (UpdataTransition(delta))
	{
		return std::move(afterScene_);
	}
	DrawOwnScreen(delta);
	return ownScene;
}
