#include "Controller.h"
#include <DxLib.h>
#include <time.h>
#include "../common/Debug.h"

Controller::Controller()
{
    isPress_ = false;
	isFinish_ = false;
}

Controller::~Controller()
{

}

bool Controller::Press(InputID id)
{
	return cntData_[id][static_cast<int>(Trg::Now)];
}

bool Controller::Pressed(InputID id)
{
	return cntData_[id][static_cast<int>(Trg::Now)] && !cntData_[id][static_cast<int>(Trg::Old)];
}

bool Controller::Released(InputID id)
{
	return !cntData_[id][static_cast<int>(Trg::Now)] && cntData_[id][static_cast<int>(Trg::Old)];
}

std::string Controller::LongPress(InputID id, double limit, double delta)
{
	if (!isPress_)
	{
		if (Press(InputID::Attack))
		{
			isPress_ = true;
			PressCount_ = 0;
		}
	}
	else
	{
		PressCount_ += delta;
		if (!Press(InputID::Attack))
		{
			isPress_ = false;
			isFinish_ = true;
		}

		if (isFinish_)
		{
			isFinish_ = false;
			if (PressCount_ < limit)
			{
				return "Attack";
			}
			else
			{
				return "LongAttack";
			}
		}
	}
	return "";
}
