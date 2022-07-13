#pragma once
#include <map>
#include <vector>
#include <string>
#include "../common/Math.h"
#include "Component.h"

using AnimVector = std::vector<std::pair<int, int>>;

enum class State
{
	Idle,
	Down,
	Left,
	Right,
	Up,
	Dash,
	Crouch,
	Attack,
	Max
};

class Animation :
	public Component
{
public:
	Animation(const std::string& key, const std::string& name, Obj& owner);
	Animation(const std::string& key, const std::string& name, std::pair<int, std::string> id, Obj& owner);
	~Animation();
	bool Init(void);											// ������
	void Update(float delta) override;											// �X�V
	bool Draw(Math::Vector2 pos, Math::Vector2I size, bool flag);		// �`�� Draw(���W, �T�C�Y, ����)
	bool Draw(Math::Vector2 pos, Math::Vector2I size, std::string state);		// �`�� Draw(���W, �T�C�Y, ����)
	bool state(const std::string state);						// �X�e�[�^�X state(�X�e�[�^�X��)
	std::string GetKey(void);									// �L�[���擾
	std::string GetState(void);									// �X�e�[�^�X�擾
private:

	ComponentID GetID() const override;

	std::string key_;
	std::string state_;
	int animFrame_;
	int animCount_;
};

