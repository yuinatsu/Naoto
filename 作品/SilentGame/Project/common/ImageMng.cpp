#include <DxLib.h>
#include "ImageMng.h"
#include "Debug.h"

const VecInt& ImageMng::GetID(std::string key)
{
    // ‰æ‘œ‚ª“Ç‚İ‚ß‚È‚©‚Á‚½‚ç
    if (imageMap_.count(key) == 0)
    {
        DebugLog("‰æ‘œ‚Ì“Ç‚İ‚İ");
        imageMap_[key].resize(1);
        imageMap_[key][0] = LoadGraph(key.c_str());
    }
    return imageMap_[key];
}

const VecInt& ImageMng::GetID(std::string f_name, std::string key)
{
    if (imageMap_.count(key) == 0)
    {
        DebugLog("‰æ‘œ‚Ì“Ç‚İ‚İ");
        imageMap_[key].resize(1);
        imageMap_[key][0] = LoadGraph(f_name.c_str());
    }
    return imageMap_[key];
}

const VecInt& ImageMng::GetID(std::string f_name, std::string key, Vector2 divSize, Vector2 divCnt)
{
    if (imageMap_.find(key) == imageMap_.end())
    {
        imageMap_[key].resize(static_cast<__int64>(divCnt.x) * divCnt.y);

        if (LoadDivGraph(f_name.c_str(), divCnt.x * divCnt.y, divCnt.x, divCnt.y, divSize.x, divSize.y, &imageMap_[key][0], true) == -1)
        {
            DebugLog("‰æ‘œ‚Ì“Ç‚İ‚İ¸”s");
            //DebugLog("f_name = ", f_name.c_str());
            //DebugLog("key = ", key.c_str());
            //DebugLog("divCnt.x * divCnt.y = ", divCnt.x * divCnt.y);
            //DebugLog("divCnt.x = ", divCnt.x);
            //DebugLog("divCnt.y =  ", divCnt.y);
            //DebugLog("divSize.x = ", divSize.x);
            //DebugLog("divSize.y = ", divSize.y);
        }
    }
    return imageMap_[key];
}

const VecInt& ImageMng::GetID(std::string f_name, std::string key, Vector2I divSize, Vector2I divCnt)
{
    if (imageMap_.count(key) == 0)
    {
        imageMap_[key].resize(divCnt.x * divCnt.y);
        if (LoadDivGraph(f_name.c_str(), divCnt.x * divCnt.y, divCnt.x, divCnt.y, divSize.x, divSize.y, &imageMap_[key][0], true) == -1)
        {
            DebugLog("‰æ‘œ‚Ì“Ç‚İ‚İ¸”s");
        }
    }
    return imageMap_[key];
}

ImageMng::ImageMng()
{
}

ImageMng::~ImageMng()
{
}
