#pragma once
#include "BaseScene.h"

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	// 静的シングルトン
	static SceneMng& GetInstance()
	{
		static SceneMng s_Instance;
		return s_Instance;
	}
	// 実行処理
	void Run(void);
private:
	// 初期化処理
	bool SysInit(void);
	void Update(void);
	void Draw(float delta);
	bool InitFlag_;

	uniqueScene scene_;

	SceneMng();
	~SceneMng();
};

