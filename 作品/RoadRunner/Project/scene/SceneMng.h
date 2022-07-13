#pragma once
#include <memory>
#include "../common/Vector2.h"
#include "BaseScene.h"

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	static SceneMng& GetInstance()
	{
		static SceneMng s_Instance;
		return s_Instance;
	}
	void Run();
	void Draw();
	const Vector2 scnArea_;					// 画面解像度
	const Vector2 worldArea_;				// ゲームの世界のチップ数
	const Vector2 viewArea_;				// 表示チップ数
	const Vector2 chipSize_;				// １チップ当たりのドット数
	const Vector2 drawOffset_;				// 画面左上からのゲームエリア
private:
	uniqueBaseScene scene_;					// BaseScene* scene_ に unique_ptrを含めた
	void Init();
	bool SysInit();
	SceneMng();
	~SceneMng();
};

