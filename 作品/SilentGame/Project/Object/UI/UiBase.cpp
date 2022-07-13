#include <DxLib.h>
#include "UiBase.h"
#include "../../Input/Pad.h"
#include "../../Input/Keyboard.h"

UiBase::UiBase()
{
}

UiBase::UiBase(const Math::Vector2& pos, const Math::Vector2& scrSize) : pos_(pos), scrSize_(scrSize)
{
	if (GetJoypadNum())
	{
		// ゲームパッド
		controller_ = std::make_unique<Pad>();
	}
	else
	{
		// キーボード
		controller_ = std::make_unique<Keyboard>();
	}
	screen_ = MakeScreen(scrSize_.x, scrSize_.y, true);
	isAlive_ = true;
}

void UiBase::Draw(void)
{
	DrawGraph((int)pos_.x, (int)pos_.y, screen_, true);
}
