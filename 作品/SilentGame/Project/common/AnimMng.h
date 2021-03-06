#pragma once
#include "../Resource/Tmx/TmxObj.h"
#include "../Component/Animation.h"

#define lpAnimMng AnimMng::GetInstance()

class AnimMng
{
public:
	static AnimMng& GetInstance()
	{
		static AnimMng s_Instance;
		return s_Instance;
	}
	// AnimをItemから設定する(XmlItem)
	bool CheckAnim(std::string key, std::string state);
	bool SetXml(std::string key, std::string f_name);
	bool SetItem(std::string key, const std::string state);
	bool SetAnim(std::string key, const std::string state, AnimVector& data);

	int GetAnimID(std::string key, std::string state, int animframe);
	int GetAnimFrame(std::string key, std::string state, int animframe);
	int GetAnimSize(std::string key, std::string state);

	Math::Vector2 GetImageSize(std::string key);
private:
	std::map<std::string, std::map<std::string, AnimVector>> animMap_;
	TmxObj tmx_;
	std::map<std::string, XmlItem> xmlItem_;
};

