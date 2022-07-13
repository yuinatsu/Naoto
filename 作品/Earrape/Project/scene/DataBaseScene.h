#pragma once
#include "BaseScene.h"
#include "../common/Vector2.h"

#define lpDataBaseScene DataBaseScene::GetInstance()

class DataBaseScene :
	public BaseScene
{
public:
	static DataBaseScene& GetInstance(void)
	{
		static DataBaseScene s_Instance;
		return s_Instance;
	}
	DataBaseScene();
	~DataBaseScene();
	SCN_ID Update(char* keyData, char* keyDataOld) override;
	void Draw(void) override;	// グラフィックの描画
	bool Init(void) override;	// 初期化
	bool Release(void) override;	// リソースの解放
private:
	int dbLogoBO_, dbLogoBW_, section1_BO_, section1_BW_, section2_BO_, section2_BW_, dbbg_;

	int atfSE_;
	bool sctFlag1_, sctFlag2_;

	int blinkCnt_;

	Vector2 pos_;
};

