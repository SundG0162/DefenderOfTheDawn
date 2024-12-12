#pragma once
#include "PlayerDevice.h"
class Upgrade : public PlayerDevice
{
public:
	Upgrade(Sprite* icon, const wstring& title, const wstring& description);
	virtual ~Upgrade();
public:
	virtual void applyUpgrade() abstract;
public:
	Sprite* getIcon() { return _icon; }
	const wstring& getTitle() { return _title; }
	const wstring& getDescription() { return _description; }
	const int& getCurrentLevel() { return _currentLevel; }
	void levelUp() { ++_currentLevel; }
	bool isValid() { return _currentLevel != _maxLevel; }
protected:
	Sprite* _icon;
	wstring _title;
	wstring _description;
	int _currentLevel;
	int _maxLevel;
};