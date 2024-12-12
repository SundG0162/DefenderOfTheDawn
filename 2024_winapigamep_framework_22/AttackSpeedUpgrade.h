#pragma once
#include "Upgrade.h"
class StatComponent;
class AttackSpeedUpgrade : public Upgrade
{
public:
	AttackSpeedUpgrade(Sprite* icon, const wstring& title, const wstring& description);
	~AttackSpeedUpgrade();
public:
	void initialize(Player* player) override;
public:
	void applyUpgrade() override;
private:
	float _modifyValues[5] = { -0.3f, -0.5f, -0.7f, -0.9f, -1.1f };
	StatComponent* _statComponent;
};

