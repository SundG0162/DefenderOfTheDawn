#pragma once
#include "WindowUI.h"
class PowerGenerator : public WindowUI
{
public:
	PowerGenerator(const Vector2& position, const Vector2& size);
	~PowerGenerator();
public:
	void update() override;
private:
	int _currentIndex;
	wstring _keys[4];
};