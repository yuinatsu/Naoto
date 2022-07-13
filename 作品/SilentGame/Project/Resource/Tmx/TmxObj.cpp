#include "TmxObj.h"
#include <sstream>
#include "../../common/ImageMng.h"
#include "../../common/Math.h"
#include "../../common/Debug.h"
#include <DxLib.h>

using namespace Math;

TmxObj::TmxObj()
{
    version_["1.8.2"] = 1;
    firstGID_ = 0;
    layerSize_ = 0;
}

TmxObj::~TmxObj()
{
}

bool TmxObj::LoadTSX(std::string fileName)
{
    rapidxml::file<> xmlFileName = fileName.c_str();
    // ファイルを開いてデータを渡す
    tsxDoc_.parse<0>(xmlFileName.data());
    rapidxml::xml_node<>* tileset = tsxDoc_.first_node("tileset");

    if (!CheckTiledVersion(tileset))
    {
        return false;
    }
    // 子のノードを取得
    auto imageNode = tileset->first_node("image");
    // ファイル名の取得
    std::string source = imageNode->first_attribute("source")->value();
    auto Source = source.substr(source.find_first_of("/") + 1);
    // パス情報を抜いてkeyNameに入れる
    auto keyName = source.substr(source.find_last_of("/") + 1);

    // サイズの取得
    auto tilewidth = atoi(tileset->first_attribute("tilewidth")->value());
    auto tileheight = atoi(tileset->first_attribute("tileheight")->value());
    // 分割数の取得
    auto divCntX = atoi(tileset->first_attribute("columns")->value());
    auto divCntY = atoi(tileset->first_attribute("tilecount")->value()) / divCntX;;

    lpImageMng.GetID("Resource/"+Source, keyName, Vector2I{tilewidth,tileheight}, Vector2I{divCntX,divCntY});
    return true;
}

bool TmxObj::LoadTMX(std::string fileName)
{
    // ファイル読み込み
    rapidxml::file<> xmlFileName = fileName.c_str();
    // ファイルを開いてデータを渡す
    tmxDoc_.parse<0>(xmlFileName.data());
    // 先頭にmapノードの取得
    rapidxml::xml_node<>* mapNode = tmxDoc_.first_node("map");
    if (!CheckTiledVersion(mapNode))
    {
        return false;
    }
    auto tileset = mapNode->first_node("tileset");
    if (!LoadTSX(fileName.substr(0, fileName.find_last_of("/") + 1) + tileset->first_attribute("source")->value()))
    {
        return false;
    }

    firstGID_ = atoi(tileset->first_attribute("firstgid")->value());
    layerSize_ = atoi(mapNode->first_attribute("nextlayerid")->value());
    worldArea_ = Vector2I{ atoi(mapNode->first_attribute("width")->value()),atoi(mapNode->first_attribute("height")->value()) };
    tileSize_ = Vector2I{ atoi(mapNode->first_attribute("tilewidth")->value()),atoi(mapNode->first_attribute("tileheight")->value()) };
    return SetMap();
}

XmlItem TmxObj::LoadXML(std::string fileName)
{
    rapidxml::file<> xmlFile = fileName.c_str();
    tsxDoc_.parse<0>(xmlFile.data());
    //DebugLog("filename = ", fileName.c_str());

    // imageノードの取り出し
    auto image = tsxDoc_.first_node();
    // imageの情報
    if (image != nullptr)
    {
        for (auto atr = image->first_attribute(); atr != nullptr; atr = atr->next_attribute())
        {
            // mapのkeyにnameを使って値を入れる
            xml_.item_[atr->name()] = atr->value();
        }
        std::string dirname;
        // アニメーション情報
        for (auto animation = image->first_node("animation"); animation != nullptr; animation = animation->next_sibling())
        {
            if (animation)
            {
                for (auto atr = animation->first_attribute(); atr != nullptr; atr = atr->next_attribute())
                {
                    std::string name = atr->name();
                    if (name == "name")
                    {
                        dirname = atr->value();
                        //DebugLog("dirname = ", dirname);
                    }
                    else if (name == "loop")
                    {
                        xml_.loop_[dirname] = std::atoi(atr->value());
                        //DebugLog("loop = ", xml_.loop_[dirname]);
                    }
                }
            }
            std::pair<int, int> tmppair;
            for (auto datasib = animation->first_node(); datasib != nullptr; datasib = datasib->next_sibling())
            {
                if (datasib) {
                    for (auto atr = datasib->first_attribute(); atr != nullptr; atr = atr->next_attribute())
                    {
                        std::string name = atr->name();
                        if (name == "count")
                        {
                            tmppair.first = std::atoi(atr->value());
                            //DebugLog("count = ", tmppair.first);
                        }
                        else if (name == "frame")
                        {
                            tmppair.second = std::atoi(atr->value());
                            //DebugLog("frame = ", tmppair.second);
                        }
                    }
                    xml_.data_[dirname].emplace_back(tmppair);
                }
            }
        }
    }
    // 全体のチップサイズ
    std::string source = xml_.item_["source"].substr(xml_.item_["source"].find_first_of("/") + 1);
    //source = "Resource/" + source;
    //DebugLog("source = ", source);
    //DebugLog("name = ", xml_.item_["name"]);
    //DebugLog("width = ", std::atoi(xml_.item_["width"].c_str()));
    //DebugLog("height = ", std::atoi(xml_.item_["height"].c_str()));
    //DebugLog("divwidth = ", std::atoi(xml_.item_["divwidth"].c_str()));
    //DebugLog("divheight = ", std::atoi(xml_.item_["divheight"].c_str()));

    // 画像の読み込み
    lpImageMng.GetID(
        source,
        xml_.item_["name"],
        Vector2(std::atoi(xml_.item_["width"].c_str()), std::atoi(xml_.item_["height"].c_str())),
        Vector2(std::atoi(xml_.item_["divwidth"].c_str()), std::atoi(xml_.item_["divheight"].c_str()))
    );
    return xml_;
}

bool TmxObj::SetMap(void)
{
    rapidxml::xml_node<>* mapNode = tmxDoc_.first_node("map");

    if (mapNode == nullptr)
    {
        return false;
    }
    for (auto layerNode = mapNode->first_node("layer");
        layerNode != nullptr;
        layerNode = layerNode->next_sibling())
    {
        if (layerNode == nullptr)
        {
            return false;
        }
        std::string nodeName = layerNode->first_attribute("name")->value();
        if (nodeName == "Col1" || nodeName == "Col2" )
        {
            continue;
        }

        auto layer = mapData_.try_emplace(layerNode->first_attribute("name")->value());
        if (layer.second)
        {
            layer.first->second.resize(static_cast<__int64> (worldArea_.x) * worldArea_.y);
        }

        auto layerData = layerNode->first_node("data")->first_node();

        std::stringstream dataStream;
        dataStream << layerData->value();
        for (auto& data : layer.first->second)
        {
            std::string numStr;
            getline(dataStream, numStr, ',');
            data = atoi(numStr.c_str());
        }
    }
    auto colNode = mapNode->first_node("objectgroup");
    while (colNode)
    {
        auto colName = colNode->first_attribute("name")->value_size();
        if (static_cast<std::string>(colNode->first_attribute("name")->value()) == "Col1")
        {
            for (auto objectNode = colNode->first_node("object");
                objectNode != nullptr;
                objectNode = objectNode->next_sibling())
            {
                if (objectNode == nullptr)
                {
                    return false;
                }
                auto colX = atof(objectNode->first_attribute("x")->value());
                auto colY = atof(objectNode->first_attribute("y")->value());
                colList_.push_back(
                    {
                    Vector2{static_cast<float>(colX),static_cast<float>(colY)},     // 左上頂点
                    Vector2{ static_cast<float>(atof(objectNode->first_attribute("width")->value())),static_cast<float>(atof(objectNode->first_attribute("height")->value())) }     // 幅と高さ
                    }
                );
            }
        }
        if (static_cast<std::string>(colNode->first_attribute("name")->value()) == "Col2")
        {
            for (auto objectNode = colNode->first_node("object");
                objectNode != nullptr;
                objectNode = objectNode->next_sibling())
            {
                if (objectNode == nullptr)
                {
                    return false;
                }
                auto colX = atof(objectNode->first_attribute("x")->value());
                auto colY = atof(objectNode->first_attribute("y")->value());
                col2List_.push_back(
                    {
                    Vector2{static_cast<float>(colX),static_cast<float>(colY)},     // 左上頂点
                    Vector2{ static_cast<float>(atof(objectNode->first_attribute("width")->value())),static_cast<float>(atof(objectNode->first_attribute("height")->value())) }     // 幅と高さ
                    }
                );
            }
        }
        // 次のノードに移動
        colNode = colNode->next_sibling();
    }
    return false;
}

const Math::Vector2I& TmxObj::GetWorldArea(void)
{
    return worldArea_;
}

const Math::Vector2I& TmxObj::GetTileSize(void)
{
    return tileSize_;
}

const unsigned int TmxObj::GetLayerSize(void)
{
    return layerSize_;
}

const unsigned int TmxObj::GetFirstGID(void)
{
    return firstGID_;
}

const MapData& TmxObj::GetMapData(void)
{
    return mapData_;
}

const int TmxObj::GetMapData(std::string layer, Math::Vector2I pos)
{
    auto chipPos = pos / tileSize_;
    return GetMapData(layer, chipPos.x, chipPos.y);
}

const int TmxObj::GetMapData(std::string layer, int x, int y)
{
    if (mapData_.count(layer) == 0)
    {
        return 0;
    }
    int point = x + (y * worldArea_.x);
    if (point >= 0 && point < mapData_[layer].size())
    {
        return mapData_[layer][point];
    }
    else
    {
        return 0;
    }
    return 0;
}

ColList& TmxObj::GetColList(void)
{
    return colList_;
}

ColList& TmxObj::GetCol2List(void)
{
    return col2List_;
}

bool TmxObj::CheckTiledVersion(rapidxml::xml_node<>* node)
{
    if (node == nullptr)
    {
        return false;
    }
    auto tiledVersion = node->first_attribute("tiledversion");
    // virsion_の中にtiledversion->value()の数値があるかを調べる
    if (!version_.count(tiledVersion->value()))
    {
        return false;
    }
    if (!version_[tiledVersion->value()])
    {
        return false;
    }
    return true;
}
