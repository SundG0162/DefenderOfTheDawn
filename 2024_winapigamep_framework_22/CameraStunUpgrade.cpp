#include "pch.h"
#include "CameraStunUpgrade.h"
#include "StatComponent.h"
#include "Stat.h"
#include "Player.h"

CameraStunUpgrade::CameraStunUpgrade(Sprite* icon, const wstring& title, const wstring& description) : Upgrade(icon, title, description)
{
	_maxLevel = 3;
}

CameraStunUpgrade::~CameraStunUpgrade()
{
}

void CameraStunUpgrade::initialize(Player* player)
{
	PlayerDevice::initialize(player);
	_statComponent = player->getComponent<StatComponent>();
}

void CameraStunUpgrade::applyUpgrade()
{
	levelUp();
	_statComponent->getStat(L"CameraStun")->addModifier(this, _modifyValues[_currentLevel - 1]);
}
