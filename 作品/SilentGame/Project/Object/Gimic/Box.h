#pragma once
#include <list>
#include "../Obj.h"
#include "../../common/Math.h"

struct Squar;
class ObjManager;
class UiBase;

enum class ItemName;

class Box :
	public Obj
{
public:
	//Alert(CameraMng& cam);
	Box(UiBase& itemUi,const Math::Vector2& pos, ObjManager& objMng, ItemName itemName);
	~Box();
	void Init(void);
	void Update(double delta) override;
	void Draw(const Math::Vector2& drawoffset) override;
	// �����󂢂Ă��邩��n��
	bool GetFlag(void);
private:

	ObjID GetObjID(void) override { return ObjID::Box; }

	// ���Ɏ������������Ă��邩
	bool BelFlag_;

	// �󂢂Ă��邩�t���O
	bool flag_;
	
	// �����Ă���A�C�e���̎��
	ItemName itemName_;

	// �������̕`��P�x�̒���
	float sColor_;
	bool scFlag_;

	std::unique_ptr<Squar> squar_;
	
	// �I�u�W�F�N�g�}�l�[�W���[
	ObjManager& objMng_;

	UiBase& itemUi_;
};

