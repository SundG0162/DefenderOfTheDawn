#pragma once
#include "Upgrade.h"
class StatComponent;
class DamageUpgrade : public Upgrade
{
public:
	DamageUpgrade(Sprite* icon, const wstring& title, const wstring& description);
	~DamageUpgrade();
public:
	void initialize(Player* player) override;
public:
	void applyUpgrade() override;
private:
	int _modifyValues[4] = { 1, 2, 4, 5};
	StatComponent* _statComponent;
};

