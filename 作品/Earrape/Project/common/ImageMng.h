#pragma once
#include <map>	// 連想配列
#include <vector>	// メモリの連続性、非連続性
#include <string>
#include "Vector2.h"

#define lpImageMng ImageMng::GetInstance()	// lp: long pointer
using VecInt = std::vector<int>;	// int型を管理するvector

class ImageMng
{
public:
	static ImageMng& GetInstance(void)
	{
		static ImageMng s_Instance;
		return s_Instance;
	}
	const VecInt& GetID(std::string key);	// 表示用
	const VecInt& GetID(std::string f_name, std::string key, Vector2 divSize, Vector2 divCnt);	// ロード用

private:
	ImageMng();
	~ImageMng();

	std::map<std::string, VecInt> imgMap_;
};

//静的シングルトンの書き方
//１．コンストラクタ、デストラクタを書く(privateで自由にインスタンスできないようにする)
//２．staticのローカル変数をpulicに書く(返り値はポインタor参照)、参照の場合はプロトタイプ宣言
//３．２．の自分自身をreturnする