#pragma once
#include <string>
#include "../common/Math.h"
#include "ComponentID.h"
class Obj;

/// <summary> オブジェクトに機能を持たせる用の基底クラス </summary>
class Component
{
public:

	/// <summary> コンストラクタ </summary>
	/// <param name="owner"> 持ち主のオブジェクト </param>
	Component(const std::string& name,Obj& owner);

	/// <summary> デストラクタ </summary>
	virtual ~Component();

	/// <summary> 更新処理 </summary>
	/// <param name="delta"> デルタタイム </param>
	virtual void Update(float delta);

	/// <summary> コンポーネントの名前を取得 </summary>
	/// <param name=""></param>
	/// <returns> コンポーネントの名前 </returns>
	std::string_view GetName(void) const;

	virtual ComponentID GetID() const = 0;
#ifdef _DEBUG
	virtual void DbgDraw(const Math::Vector2& offset) const {}
#endif
protected:

	/// <summary> 持ち主 </summary>
	Obj& owner_;

	// 名前
	std::string name_;
};

