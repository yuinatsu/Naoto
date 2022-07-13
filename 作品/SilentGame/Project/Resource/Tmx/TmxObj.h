#pragma once
#include <map>
#include <unordered_map>
#include <string>
#include <list>
#include <vector>
#include "../../common/MapCollMng.h"
#include "../../common/Math.h"
#include "../../common/rapidxml.hpp"
#include "../../common/rapidxml_utils.hpp"

using MapData = std::map<std::string, std::vector<int>>;
using AnimData = std::pair<int, int>;									// pair<画像内の何番目か, フレーム数>
using AnimVecData = std::list<AnimData>;								// AnimData をlistで格納したデータ

// xmlデータ格納
struct XmlItem
{
	std::map<std::string, std::string> item_;							// map<アイテム名, 要素>
	std::map<std::string, int> loop_;									// map<アニメーション名, ループ有無>
	std::map<std::string, AnimVecData> data_;							// map<アニメーション名, アニメーションデータ>
};

class TmxObj
{
public:
	TmxObj();
	~TmxObj();
	bool LoadTSX(std::string fileName);
	bool LoadTMX(std::string fileName);
	XmlItem LoadXML(std::string fileName);
	bool SetMap(void);
	// ワールド座標の取得
	const Math::Vector2I& GetWorldArea(void);
	// タイルサイズの取得
	const Math::Vector2I& GetTileSize(void);
	// レイヤーサイズの取得
	const unsigned int GetLayerSize(void);
	// GIDの取得
	const unsigned int GetFirstGID(void);
	// マップデータの取得
	const MapData& GetMapData(void);
	// posは座標としたマップデータを取得
	const int GetMapData(std::string layer, Math::Vector2I pos);
	// x,yはマス目数としたマップデータの取得
	const int GetMapData(std::string layer, int x, int y);
	// Collisionを取得
	ColList& GetColList(void);
	// Collision2を取得
	ColList& GetCol2List(void);
private:
	bool CheckTiledVersion(rapidxml::xml_node<>* node);
	std::map<std::string, int> version_;
	// TMX
	rapidxml::xml_document<> tmxDoc_;
	unsigned int firstGID_;
	unsigned int layerSize_;
	Math::Vector2I worldArea_;
	Math::Vector2I tileSize_;
	MapData mapData_;
	ColList colList_;				// プレイヤーとエネミーどちらにも反応するコリジョンデータ
	ColList col2List_;				// プレイヤーのみに反応するコリジョンデータ
	// TSX
	rapidxml::xml_document<> tsxDoc_;
	// XML
	XmlItem xml_;
};

