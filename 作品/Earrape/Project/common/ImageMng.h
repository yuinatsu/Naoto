#pragma once
#include <map>	// �A�z�z��
#include <vector>	// �������̘A�����A��A����
#include <string>
#include "Vector2.h"

#define lpImageMng ImageMng::GetInstance()	// lp: long pointer
using VecInt = std::vector<int>;	// int�^���Ǘ�����vector

class ImageMng
{
public:
	static ImageMng& GetInstance(void)
	{
		static ImageMng s_Instance;
		return s_Instance;
	}
	const VecInt& GetID(std::string key);	// �\���p
	const VecInt& GetID(std::string f_name, std::string key, Vector2 divSize, Vector2 divCnt);	// ���[�h�p

private:
	ImageMng();
	~ImageMng();

	std::map<std::string, VecInt> imgMap_;
};

//�ÓI�V���O���g���̏�����
//�P�D�R���X�g���N�^�A�f�X�g���N�^������(private�Ŏ��R�ɃC���X�^���X�ł��Ȃ��悤�ɂ���)
//�Q�Dstatic�̃��[�J���ϐ���pulic�ɏ���(�Ԃ�l�̓|�C���^or�Q��)�A�Q�Ƃ̏ꍇ�̓v���g�^�C�v�錾
//�R�D�Q�D�̎������g��return����