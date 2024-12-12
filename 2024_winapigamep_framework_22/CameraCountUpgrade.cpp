#include "pch.h"
#include "CameraCountUpgrade.h"
#include "StatComponent.h"
#include "Stat.h"
#include "Player.h"

CameraCountUpgrade::CameraCountUpgrade(Sprite* icon, const wstring& title, const wstring& description) : Upgrade(icon, title, description)
{
	_maxLevel = 1;
}

CameraCountUpgrade::~CameraCountUpgrade()
{
}

void CameraCountUpgrade::initialize(Player* player)
{
	PlayerDevice::initialize(player);
	_statComponent = player->getComponent<StatComponent>();
}

void CameraCountUpgrade::applyUpgrade()
{
	levelUp();
	_statComponent->getStat(L"CameraCount")->addModifier(this, _modifyValues[_currentLevel - 1]);
}
