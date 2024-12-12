#include "pch.h"
#include "Upgrade.h"

Upgrade::Upgrade(Sprite* icon, const wstring& title, const wstring& description)
{
	_icon = icon;
	_title = title;
	_description = description;
	_maxLevel = 0;
	_currentLevel = 0;
}

Upgrade::~Upgrade()
{
}
