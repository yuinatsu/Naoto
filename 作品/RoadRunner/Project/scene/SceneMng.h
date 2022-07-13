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
	const Vector2 scnArea_;					// ��ʉ𑜓x
	const Vector2 worldArea_;				// �Q�[���̐��E�̃`�b�v��
	const Vector2 viewArea_;				// �\���`�b�v��
	const Vector2 chipSize_;				// �P�`�b�v������̃h�b�g��
	const Vector2 drawOffset_;				// ��ʍ��ォ��̃Q�[���G���A
private:
	uniqueBaseScene scene_;					// BaseScene* scene_ �� unique_ptr���܂߂�
	void Init();
	bool SysInit();
	SceneMng();
	~SceneMng();
};

