#include <DxLib.h>
#include "CameraMng.h"
#include "../ImageMng.h"
#include <algorithm>

bool CameraMng::Init(std::string map, std::shared_ptr<TmxObj>& tmxObj)
{
	map_ = map;
    Viewsize_ = { 960,540 };

	// マップのサイズを取得
	auto worldSize = tmxObj->GetWorldArea() * tmxObj->GetTileSize();

	// 上方向の制限
	rect_.top = Viewsize_.y / 2.0f;		// 0から表示するサイズの半分

	// 下方向の制限
	rect_.bottom = worldSize.y - Viewsize_.y / 2.0f;		// マップの一番下から上に表示サイズの半分

	// 左方向の制限
	rect_.left = Viewsize_.x / 2.0f;					// 0から表示するサイズの半分

	// 右方向の制限
	rect_.right = worldSize.x - Viewsize_.x / 2.0f;		// マップの一番右から左に表示サイズの半分

	// カメラ初期位置
	defPos_ = { rect_.left,rect_.top };
    return true;
}

bool CameraMng::Update(const Math::Vector2& pos)
{
	/*pos_ = Math::Vector2{ (float)std::clamp(static_cast<int>(pos.x), -960, 0) , (float)std::clamp(static_cast<int>(pos.y), -540, 0) };*/
	// マップのサイズを取得
	pos_ = { std::clamp(pos.x, rect_.left, rect_.right), std::clamp(pos.y, rect_.top, rect_.bottom) };
    return true;
}

//bool CameraMng::Draw(TmxObj& tmxObj)
//{
//    auto WorldArea = tmxObj.GetWorldArea();
//    auto TileSize = tmxObj.GetTileSize();
//	for (const auto& layer : tmxObj.GetMapData())
//	{
//		for (int y = 0; y < WorldArea.y; y++)
//		{
//			for (int x = 0; x < WorldArea.x; x++)
//			{
//				auto image = y * WorldArea.x + x;
//				if (image < layer.second.size())
//				{
//					// グラフィックidの取得
//					int gid = layer.second[static_cast<__int64>(y) * WorldArea.x + x] - tmxObj.GetFirstGID();
//					if (gid >= 0)
//					{
//						// x,yのところを座標に戻す
//						DrawGraph(x * TileSize.x + GetOffset().x, y * TileSize.y + GetOffset().y, lpImageMng.GetID(map_)[gid], true);
//					}
//				}
//			}
//		}
//	}
//    return true;
//}

Math::Vector2I CameraMng::GetViewSize()
{
	return Viewsize_;
}

const Math::Vector2 CameraMng::GetOffset(void) const
{
	// 初期位置からの座標を引いて描画用オフセットの値を返す
	return defPos_ - pos_;
}
