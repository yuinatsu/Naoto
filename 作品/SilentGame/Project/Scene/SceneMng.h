#pragma once
#include "BaseScene.h"

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	// �ÓI�V���O���g��
	static SceneMng& GetInstance()
	{
		static SceneMng s_Instance;
		return s_Instance;
	}
	// ���s����
	void Run(void);
private:
	// ����������
	bool SysInit(void);
	void Update(void);
	void Draw(float delta);
	bool InitFlag_;

	uniqueScene scene_;

	SceneMng();
	~SceneMng();
};

