#pragma once
#include "../Math.h"
#include "../../Resource/Tmx/TmxObj.h"

// �J�����̐����p�\����
struct CameraRect 
{
    float top;      // ��
    float bottom;   // ��
    float left;     // ��
    float right;    // �E
};

class CameraMng
{
public:
    bool Init(std::string map, std::shared_ptr<TmxObj>& tmxObj) ;
    bool Update(const Math::Vector2& pos);
    //bool Draw(TmxObj& tmxObj);  // �������g��`��
    Math::Vector2I GetViewSize();


    /// <summary> �`��p�I�t�Z�b�g���擾���� </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const Math::Vector2 GetOffset(void) const;
private:

    // �J�����̐���
    CameraRect rect_;

    // �J�����̏����ʒu
    Math::Vector2 defPos_;

    // �J�����̕\���T�C�Y
    Math::Vector2 Viewsize_;

    // �J�����̍��W
    Math::Vector2 pos_;

    // �}�b�v��
    std::string map_;
};

