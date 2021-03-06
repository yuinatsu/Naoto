#pragma once
#include <map>
#include <string>

enum class InputType
{
	NOW,				// 現在の入力情報
	OLD,				// １つ前の入力情報
};

using InputData = std::map<std::string, int>;

class Obj;

class Input
{
public:
	Input();
	virtual ~Input();
	virtual bool Update(Obj& obj) = 0;				// 継承先でのみ使用
	virtual bool Update(Obj& obj, Obj& other);
	const InputData& GetData(InputType type);
private:

protected:
	InputData data_;
	InputData dataOld_;
};

