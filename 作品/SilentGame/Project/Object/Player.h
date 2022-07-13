#pragma once
#include <map>
#include <list>
#include <sstream>
#include "Unit.h"
#include "state/PlayerState.h"

class Player :
    public Unit
{
public:
    /// <summary> �R���X�g���N�^  </summary>
    /// <param name="cntType"> �R���g���[����� </param>
    /// <param name="pos"> �������W </param>
    Player(CntType cntType, std::shared_ptr<TmxObj> tmx, Math::Vector2 pos);
    ~Player();
private:
    /// <summary> ������ </summary>
    /// <param name="cntType"> �R���g���[���[�̎�� </param>
    /// <returns> ������true���s��false </returns>
    bool Init(CntType cntType);
    
    /// <summary> �X�V </summary>
    /// <param name="delta"> �f���^�^�C�� </param>
    void Update(double delta)override;

    /// <summary> �`�� </summary>
    /// <param name="offset"> ��ʃI�t�Z�b�g </param>
    void Draw(const Math::Vector2& offset)override;

    void DrawEffect(const Math::Vector2& offset);

    /// <summary> �A�j���[�V�����C���[�W�ǂݍ��� </summary>
    /// <returns> ������true���s��false </returns>
    bool LoadAnim(void);

    /// <summary> ID�擾 </summary>
    /// <returns> ObjID::Player </returns>
    ObjID GetObjID(void) override { return ObjID::Player; };

    /// <summary> �v���C���[�A�N�V���� </summary>
    std::vector<char> stateVec_;
    rapidxml::xml_document<> stateDoc_;
    rapidxml::xml_node<>* stateNode_;
    animNode* animNode_;
};

