#pragma once
#include "Component.h"
class StatComponent;
class UpgradeUI;
class Upgrade;
class UpgradeComponent : public Component
{
public:
	UpgradeComponent();
	~UpgradeComponent();
public:
	void initialize();
	void lateUpdate() override;
	void render(HDC hDC) override;
public:
	void setRandomUpgrade();
	bool isUpgrading() { return _upgradeFlag; }
private:
	vector<Upgrade*> _upgrades;
	vector<Upgrade*> _finishedUpgrade;
	bool _upgradeFlag;
};

