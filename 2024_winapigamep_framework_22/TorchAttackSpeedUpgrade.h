#pragma once
#include "Upgrade.h"
class StatComponent;
class TorchAttackSpeedUpgrade : public Upgrade
{
public:
	TorchAttackSpeedUpgrade(Sprite* icon, const wstring& title, const wstring& description);
	~TorchAttackSpeedUpgrade();
public:
	void initialize(Player* player) override;
public:
	void applyUpgrade() override;
private:
	float _modifyValues[2] = { -0.25f,-0.5f };
	StatComponent* _statComponent;
};

