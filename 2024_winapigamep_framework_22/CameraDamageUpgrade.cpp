#include "pch.h"
#include "CameraDamageUpgrade.h"
#include "StatComponent.h"
#include "Stat.h"
#include "Player.h"

CameraDamageUpgrade::CameraDamageUpgrade(Sprite* icon, const wstring& title, const wstring& description) : Upgrade(icon, title, description)
{
	_maxLevel = 3;
}

CameraDamageUpgrade ::~CameraDamageUpgrade()
{
}

void CameraDamageUpgrade::initialize(Player* player)
{
	PlayerDevice::initialize(player);
	_statComponent = player->getComponent<StatComponent>();
}

void CameraDamageUpgrade::applyUpgrade()
{
	levelUp();
	_statComponent->getStat(L"CameraDamage")->addModifier(this, _modifyValues[_currentLevel - 1]);
}
