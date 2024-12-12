#pragma once
#include "Upgrade.h"
class StatComponent;
class CameraCountUpgrade : public Upgrade
{
public:
	CameraCountUpgrade(Sprite* icon, const wstring& title, const wstring& description);
	~CameraCountUpgrade();
public:
	void initialize(Player* player) override;
public:
	void applyUpgrade() override;
private:
	int _modifyValues[1] = { -1 };
	StatComponent* _statComponent;
};

