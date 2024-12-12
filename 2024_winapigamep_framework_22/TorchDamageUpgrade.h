#pragma once
#include "Upgrade.h"
class StatComponent;
class TorchDamageUpgrade : public Upgrade
{
public:
	TorchDamageUpgrade(Sprite* icon, const wstring& title, const wstring& description);
	~TorchDamageUpgrade();
public:
	void initialize(Player* player) override;
public:
	void applyUpgrade() override;
private:
	int _modifyValues[2] = { 2,3 };
	StatComponent* _statComponent;
};

