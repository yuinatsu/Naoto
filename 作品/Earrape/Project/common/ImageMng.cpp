#include <DxLib.h>
#include "ImageMng.h"
#include "../_debug/_DebugConOut.h"

//--------------------------------------------------------------------------
//●ファイル名の取得
//	key：ファイル名
//--------------------------------------------------------------------------
const VecInt& ImageMng::GetID(std::string key)
{
	if (imgMap_.find(key) == imgMap_.end())
	{
		imgMap_[key].resize(1);
		imgMap_[key][0] = LoadGraph(key.c_str());
	}
	return imgMap_[key];
}

//--------------------------------------------------------------------------
//●ファイル名の取得（読み込み用）
//	f_name：ファイル名（LoadDivGraph用）
//	key：ファイル名（配列用）
//	divSize：分割サイズ
//	divCnt：分割数
//--------------------------------------------------------------------------
const VecInt& ImageMng::GetID(std::string f_name, std::string key, Vector2 divSize, Vector2 divCnt)
{
	if (imgMap_.find(key) == imgMap_.end())
	{
		TRACE("ファイルの読み込み\n");
		imgMap_[key].resize(divCnt.x * divCnt.y);

		// 画像を読み込んでいない場合読み込む
		LoadDivGraph(f_name.c_str(), (divCnt.x * divCnt.y), divCnt.x, divCnt.y, divSize.x, divSize.y, &imgMap_[key][0], true);
	}
	return imgMap_[key];
}

//--------------------------------------------------------------------------
//●コンストラクタ
//--------------------------------------------------------------------------
ImageMng::ImageMng()
{
}

//--------------------------------------------------------------------------
//●デストラクタ
//--------------------------------------------------------------------------
ImageMng::~ImageMng()
{
}
