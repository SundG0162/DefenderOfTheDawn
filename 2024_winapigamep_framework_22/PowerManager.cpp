#include "pch.h"
#include "PowerManager.h"
#include "ResultManager.h"

void PowerManager::initialize()
{
	OnPowerChangeEvent.clear();
	_power = 0;
}

void PowerManager::modifyPower(int value)
{
	int prev = _power;
	if (value > 0)
	{
		GET_SINGLETON(ResultManager)->modifyTotalPower(value);
	}
	_power += value;
	OnPowerChangeEvent.invoke(prev, _power);
}

bool PowerManager::trySpendPower(int value)
{
	if (_power >= value)
	{
		modifyPower(-value);
		return true;
	}
	return false;
}
