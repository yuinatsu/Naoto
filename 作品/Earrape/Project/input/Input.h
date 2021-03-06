#pragma once
#include <string>
#include <map>

using InputData = std::map<std::string, int>;

enum class InputType
{
	NOW,	// 現在の入力情報
	OLD		// 過去の入力情報
};

class Obj;

class Input
{
public:
	Input();
	virtual ~Input();
	virtual bool Update(void) = 0;
	const InputData& GetData(InputType type);
private:
protected:
	InputData data_;
	InputData dataOld_;
};
