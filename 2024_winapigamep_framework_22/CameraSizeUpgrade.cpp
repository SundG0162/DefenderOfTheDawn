#include "pch.h"
#include "CameraSizeUpgrade.h"
#include "StatComponent.h"
#include "Stat.h"
#include "Player.h"

CameraSizeUpgrade::CameraSizeUpgrade(Sprite* icon, const wstring& title, const wstring& description) : Upgrade(icon, title, description)
{
	_maxLevel = 3;
}

CameraSizeUpgrade ::~CameraSizeUpgrade()
{
}

void CameraSizeUpgrade::initialize(Player* player)
{
	PlayerDevice::initialize(player);
	_statComponent = player->getComponent<StatComponent>();
}

void CameraSizeUpgrade::applyUpgrade()
{
	levelUp();
	_statComponent->getStat(L"CameraSize")->addModifier(this, _modifyValues[_currentLevel - 1]);
}
