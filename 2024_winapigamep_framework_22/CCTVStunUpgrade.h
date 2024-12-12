#pragma once
#include "Upgrade.h"
class StatComponent;
class CCTVStunUpgrade : public Upgrade
{
public:
	CCTVStunUpgrade(Sprite* icon, const wstring& title, const wstring& description);
	~CCTVStunUpgrade();
public:
	void initialize(Player* player) override;
public:
	void applyUpgrade() override;
private:
	float _modifyValues[1] = { 0.2f };
	StatComponent* _statComponent;
};

