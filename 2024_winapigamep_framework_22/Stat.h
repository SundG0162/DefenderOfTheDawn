#pragma once
#include "Action.h"
class Stat
{
public:
	Stat(float baseValue);
	~Stat();
public:
	void addModifier(void* key, float value);
	void removeModifier(void* key);
public:
	void setValue(float value) { _baseValue = value; }
	float getBaseValue() { return _baseValue; }
	float getValue() { return _baseValue + _modifiedValue; };
public:
	Action<float, float> OnValueChangeEvent;
private:
	float _baseValue;
	float _modifiedValue;
	map<void*, float> _modifierMap;
};

