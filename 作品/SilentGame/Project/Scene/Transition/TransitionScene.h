#pragma once
#include "../BaseScene.h"
enum class Transition
{
    CrossFade,
    FadeInOut,
    Max
};

// ‰æ–Ê‘JˆÚ—pƒNƒ‰ƒX
class TransitionScene :
    public BaseScene
{
public:
    TransitionScene(uniqueScene beforScene, uniqueScene afterScene);
    ~TransitionScene();
private:
    bool Init(void);
    uniqueScene Update(float delta, uniqueScene ownScene) override;
    virtual bool UpdataTransition(double delta) = 0;
protected:
    Scene GetSceneID(void) override final { return Scene::Transtion; };
    uniqueScene beforScene_;
    uniqueScene afterScene_;
    bool GetFlag(void) override { return SceneFlag_; };

    double count;
};

