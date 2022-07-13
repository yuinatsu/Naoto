#pragma once
#include "Obj.h"
class Alcohol :
    public Obj
{
public:
	Alcohol(const Math::Vector2& pos);
	~Alcohol();
private:
	bool Init(void);
	void Update(double delta) override;
	void Draw(const Math::Vector2& offset)override;
	ObjID GetObjID(void) override { return ObjID::Alcohol; };
};

