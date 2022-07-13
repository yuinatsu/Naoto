#include "Input.h"

//--------------------------------------------------------------------------
//●コンストラクタ
//--------------------------------------------------------------------------
Input::Input()
{
}

//--------------------------------------------------------------------------
//●デストラクタ
//--------------------------------------------------------------------------
Input::~Input()
{
}

//--------------------------------------------------------------------------
//●データの取得（入力機器関連）
//--------------------------------------------------------------------------
const InputData& Input::GetData(InputType type)
{
	if (type == InputType::NOW)
	{
		return data_;
	}
	else
	{
		return dataOld_;
	}
}
