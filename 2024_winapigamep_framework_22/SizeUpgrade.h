#pragma once
#include "Upgrade.h"
class StatComponent;
class SizeUpgrade : public Upgrade
{
public:
	SizeUpgrade(Sprite* icon, const wstring& title, const wstring& description);
	~SizeUpgrade();
public:
	void initialize(Player* player) override;
public:
	void applyUpgrade() override;
private:
	int _modifyValues[5] = { 50, 100, 150, 200, 250 };
	StatComponent* _statComponent;
};

