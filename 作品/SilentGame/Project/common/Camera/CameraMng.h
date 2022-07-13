#pragma once
#include "../Math.h"
#include "../../Resource/Tmx/TmxObj.h"

// カメラの制限用構造体
struct CameraRect 
{
    float top;      // 上
    float bottom;   // 下
    float left;     // 左
    float right;    // 右
};

class CameraMng
{
public:
    bool Init(std::string map, std::shared_ptr<TmxObj>& tmxObj) ;
    bool Update(const Math::Vector2& pos);
    //bool Draw(TmxObj& tmxObj);  // 自分自身を描画
    Math::Vector2I GetViewSize();


    /// <summary> 描画用オフセットを取得する </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const Math::Vector2 GetOffset(void) const;
private:

    // カメラの制限
    CameraRect rect_;

    // カメラの初期位置
    Math::Vector2 defPos_;

    // カメラの表示サイズ
    Math::Vector2 Viewsize_;

    // カメラの座標
    Math::Vector2 pos_;

    // マップ名
    std::string map_;
};

