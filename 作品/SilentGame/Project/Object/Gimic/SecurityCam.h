#pragma once
#include <list>
#include "../../common/MapCollMng.h"
#include "../../common/Math.h"
#include "../../Resource/Tmx/TmxObj.h"
#include "../../common/Camera/CameraMng.h"
#include "../../common/Structure.h"
#include "../../common/Time.h"
#include "../Obj.h"

using Vector2 = Math::Vector2;

class Alert:
	public Obj
{
public:
	Alert(Vector2 pos,Vector2 vec, std::shared_ptr<TmxObj>& tmxObj, std::unique_ptr<Obj>& player);
	~Alert();
	void Init(void);
	void Update(double delta) override;
	// �v���C���[�������Ă��Ȃ��Ƃ��̏���
	void UpdateNoDis(const Vector2& pos, float delta);
	// �v���C���[�����������̏���
	void UpdateDis(const Vector2& pos, float delta);
	void Draw(const Math::Vector2& offset) override;
	ObjID GetObjID(void) { return ObjID::Alert; };
	// ���������̍��W��n��
	Vector2 GetSpos(void);
	// �v���C���[�����m�������ǂ������󂯎��
	bool GetpFlag(void);

private:
	// �v���C���[�������������̍��W���󂯎��
	void SetPos(const Vector2& pos);
	// �}�b�v�����󂯎��
	std::shared_ptr<TmxObj>& tmxObj_;
	// �v���C���[�̏����󂯎��
	std::unique_ptr<Obj>& player_;

	// �����̉�]���t��]��
	bool rotFlag_;
	// �����̉�]�𔽓]����܂ł̎���
	float rotTime_;
	// �v���C���[���������ǂ���
	bool pflag_;

	std::unique_ptr<Fan> fan_;
	Vector2 pos_;
	// �v���C���[���ǂꂩ�̎����ɓ��������ǂ���
	bool sFlag_;
	// �v���C���[�������ĉ��b�������̂�
	float Time_;
	// �v���C���[�������������̍��W������
	Vector2 sPos_;
};

