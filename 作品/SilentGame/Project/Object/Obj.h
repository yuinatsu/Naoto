#pragma once
#include <memory>
#include <unordered_map>
#include "../Component/ComponentID.h"
#include "../common/Math.h"
#include "../input/Controller.h"
#include "../Resource/Tmx/TmxObj.h"
#include "../common/MapCollMng.h"
#include "../Component/Animation.h"
#include <string>


class Component;

using ComponentUPTr = std::unique_ptr<Component>;
using ComponentMap = std::unordered_map<ComponentID,std::unordered_map<std::string_view, ComponentUPTr>>;

// state
struct Move;
struct Attack;
struct SpChange;
struct CheckKey;
struct SetAnime;
struct ColisionCheck;

enum class ObjID
{
	Player,
	Enemy,
	Item,
	Weapon,
	UI,
	Box,
	Alert,
	TrapAlarm,
	LandMine,
	Alcohol,
	Decoy
};

class Obj
{
public:
	Obj();
	virtual ~Obj();

	virtual void Update(double delta);
	//virtual void Draw(void) const;
	virtual void Draw(const Math::Vector2& offset);

	/// <summary> �R���|�[�l���g���擾���� </summary>
	/// <param name="id"> �擾�������R���|�[�l���g��ID </param>
	/// <returns> �R���|�[�l���g�̎Q�� </returns>
	const std::unordered_map<std::string_view, ComponentUPTr>& GetComponent(ComponentID id) const;

	/// <summary> �R���|�[�l���g���擾���� </summary>
	/// <param name="id"> �擾�������R���|�[�l���g��ID </param>
	/// <returns> �R���|�[�l���g�̎Q�� </returns>
	Component& GetComponent(ComponentID id,std::string_view name) const;

	/// <summary> ID�ɊY������R���|�[�l���g���܂܂�邩 </summary>
	/// <param name="id"> �T�������R���|�[�l���g��ID </param>
	/// <returns></returns>
	bool IncludeComponent(ComponentID id) const;

	/// <summary> ID�ɊY������R���|�[�l���g���܂܂�邩 </summary>
	/// <param name="id"> �T�������R���|�[�l���g��ID </param>
	/// <returns></returns>
	bool IncludeComponent(ComponentID id, std::string_view name) const;

	/// <summary> �R���|�[�l���g��ǉ����� </summary>
	/// <param name="component"> �ǉ��������R���|�[�l���g </param>
	/// <returns> ������true���s��false </returns>
	bool AddComponent(ComponentUPTr&& component);

	/// <summary> �R���|�[�l���g���폜���� </summary>
	/// <param name="id"> �폜�������R���|�[�l���g </param>
	/// <returns> ������true���s��false </returns>
	bool RemoveComponent(ComponentID id,std::string_view name);


	/// <summary> ���W���擾 </summary>
	/// <param name=""></param>
	/// <returns> ���W </returns>
	const Math::Vector2& GetPos(void) const;

	/// <summary> ���W���Z�b�g </summary>
	/// <param name="pos"> �Z�b�g���������W </param>
	void SetPos(const Math::Vector2& pos);

	
	virtual ObjID GetObjID(void) = 0;

	/// <summary> �ړ������x�N�g�����Z�b�g���� </summary>
	/// <param name="moveVec"></param>
	void SetMoveVec(const Math::Vector2& moveVec);

	/// <summary> �ړ������x�N�g�����擾���� </summary>
	/// <param name=""></param>
	/// <returns> �ړ������x�N�g�� </returns>
	const Math::Vector2& GetMoveVec(void) const;

	/// <summary> moveVec�Aspeed_�AspMag_�Adelta���g���ړ����� </summary>
	/// <param name="delta"></param>
	virtual void MovePos(double delta);

	/// <summary> �ړ��ł��邩�ǂ����H </summary>
	/// <param name=""></param>
	/// <returns> �ړ��ł���Ƃ�true�ł��Ȃ��Ƃ�false </returns>
	bool IsMove(void);

	/// <summary> �X�s�[�h���擾���� </summary>
	/// <param name=""> �X�s�[�h </param>
	/// <returns></returns>
	const float GetSpeed(void) const;

	/// <summary> �X�s�[�h�̔{�����擾���� </summary>
	/// <param name=""></param>
	/// <returns> �X�s�[�h�̔{�� </returns>
	const float GeSpMag(void) const;

	/// <summary> �A�C�h����ԃt���O���Z�b�g���� </summary>
	/// <param name="flag"> �Z�b�g����t���O </param>
	void SetIdleFlag(bool flag) { isIdle_ = flag; }

	/// <summary> �A�C�h����Ԃ��H </summary>
	/// <param name=""></param>
	/// <returns> �A�C�h����Ԃ̎�true�����łȂ��Ƃ�false </returns>
	const bool IsIdle(void)const { return isIdle_; }

	/// <summary> �������Ă��邩�H </summary>
	/// <param name=""></param>
	/// <returns> �������Ă���Ƃ�true���Ă��Ȃ��Ƃ�false </returns>
	const bool IsAlive(void) const { return alive_; }

	/// <summary> ���̃I�u�W�F�N�g��j�����邽�߂ɐ����t���O��false�ɂ��� </summary>
	/// <param name=""></param>
	void Destroy(void) { alive_ = false; }
	std::vector<std::pair<int, std::string>> GetItemID(void) { return itemId_; };

	void SetAtkFlag(bool flag) { atkFlag_ = flag; };
protected:

	/// <summary> �R���|�[�l���g�̍X�V���� </summary>
	/// <param name="delta"></param>
	void UpdateComponent(double delta) const;

	/// <summary> ���W </summary>
	Math::Vector2 pos_;

	/// <summary> �T�C�Y </summary>
	Math::Vector2 size_;

	/// <summary> �ړ����� </summary>
	Math::Vector2 moveVec_;

	/// <summary> �ړ��� </summary>
	float speed_;

	/// <summary> �ړ��ʔ{�� </summary>
	float spMag_;

	/// <summary> �U���� </summary>
	float atk_;

	/// <summary> �U���͔{�� </summary>
	float atkMag_;

	/// <summary> �U�����s�t���O </summary>
	float atkFlag_;

	/// <summary> �R���g���[����� </summary>
	std::unique_ptr<Controller> controller_;

	/// <summary> �f���^�^�C�� </summary>
	double delta_;

	bool isIdle_;

	// �����t���O
	bool alive_;

	bool isItemUse_;

	//Math::Vector2 colPos_;												// �����蔻��̒��S���W
	//std::map<std::string, std::list<Math::Vector2>> colVec_;				// �����蔻��̕���
	
	//MapCollMng raycast_;

	std::vector<std::pair<int, std::string>> itemId_;

	std::shared_ptr<TmxObj> tmx_;

	// friend
	friend Move;
	friend Attack;
	friend SpChange;
	friend CheckKey;
	friend SetAnime;
	friend ColisionCheck;
private:

	/// <summary> �R���|�[�l���g�ނ��}�b�v�Ŏ��� </summary>
	ComponentMap componentList_;
};

