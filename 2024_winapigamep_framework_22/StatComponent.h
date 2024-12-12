#pragma once
#include "Component.h"
class Stat;
class StatComponent : public Component
{
public:
	StatComponent();
	~StatComponent();
public:
	void lateUpdate() override;
	void render(HDC hDC) override;
public:
	void addStat(const wstring& key, Stat* stat);
	Stat* getStat(const wstring& key);
private:
	map<wstring, Stat*> _statMap;
};