#pragma once
#include "Upgrade.h"
class StatComponent;
class CameraSizeUpgrade : public Upgrade
{
public:
	CameraSizeUpgrade(Sprite* icon, const wstring& title, const wstring& description);
	~CameraSizeUpgrade();
public:
	void initialize(Player* player) override;
public:
	void applyUpgrade() override;
private:
	float _modifyValues[3] = { 30, 90, 150 };
	StatComponent* _statComponent;
};