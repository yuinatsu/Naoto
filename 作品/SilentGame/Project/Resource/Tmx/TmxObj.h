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
using AnimData = std::pair<int, int>;									// pair<�摜���̉��Ԗڂ�, �t���[����>
using AnimVecData = std::list<AnimData>;								// AnimData ��list�Ŋi�[�����f�[�^

// xml�f�[�^�i�[
struct XmlItem
{
	std::map<std::string, std::string> item_;							// map<�A�C�e����, �v�f>
	std::map<std::string, int> loop_;									// map<�A�j���[�V������, ���[�v�L��>
	std::map<std::string, AnimVecData> data_;							// map<�A�j���[�V������, �A�j���[�V�����f�[�^>
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
	// ���[���h���W�̎擾
	const Math::Vector2I& GetWorldArea(void);
	// �^�C���T�C�Y�̎擾
	const Math::Vector2I& GetTileSize(void);
	// ���C���[�T�C�Y�̎擾
	const unsigned int GetLayerSize(void);
	// GID�̎擾
	const unsigned int GetFirstGID(void);
	// �}�b�v�f�[�^�̎擾
	const MapData& GetMapData(void);
	// pos�͍��W�Ƃ����}�b�v�f�[�^���擾
	const int GetMapData(std::string layer, Math::Vector2I pos);
	// x,y�̓}�X�ڐ��Ƃ����}�b�v�f�[�^�̎擾
	const int GetMapData(std::string layer, int x, int y);
	// Collision���擾
	ColList& GetColList(void);
	// Collision2���擾
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
	ColList colList_;				// �v���C���[�ƃG�l�~�[�ǂ���ɂ���������R���W�����f�[�^
	ColList col2List_;				// �v���C���[�݂̂ɔ�������R���W�����f�[�^
	// TSX
	rapidxml::xml_document<> tsxDoc_;
	// XML
	XmlItem xml_;
};

