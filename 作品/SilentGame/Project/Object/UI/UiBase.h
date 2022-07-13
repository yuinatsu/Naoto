#pragma once
#include <memory>
#include <vector>
#include <string>
#include "../Item.h"
#include "../../common/Math.h"

struct ItemCur;

class UiBase
{
public:
	UiBase();
	UiBase(const Math::Vector2& pos, const Math::Vector2& scrSize);
	virtual ~UiBase() = default;
	virtual void Update(const double& delta) = 0;
	virtual void ItemUpdate(const double& delta) = 0;
	virtual void UIDraw(const double& delta) = 0;
	virtual void Draw(void);
	bool isAlive(void) { return isAlive_; };
	virtual bool SetItemID(std::pair<int, std::string> id) = 0;
	virtual ItemName GetUseItem() = 0;
	virtual std::vector<std::pair<int, std::string>> GetItemID() = 0;
protected:
	Math::Vector2 pos_;
	Math::Vector2I scrSize_;
	int itemID_;
	int screen_;
	bool isAlive_;
	std::unique_ptr<Controller> controller_;
	friend ItemCur;
};

