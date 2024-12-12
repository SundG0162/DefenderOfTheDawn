#pragma once
#include "Upgrade.h"
class StatComponent;
class CameraStunUpgrade : public Upgrade
{
public:
	CameraStunUpgrade(Sprite* icon, const wstring& title, const wstring& description);
	~CameraStunUpgrade();
public:
	void initialize(Player* player) override;
public:
	void applyUpgrade() override;
private:
	float _modifyValues[3] = { 0.3f, 0.6f, 1.f};
	StatComponent* _statComponent;
};

