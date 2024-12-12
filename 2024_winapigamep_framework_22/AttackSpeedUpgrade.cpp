#include "pch.h"
#include "AttackSpeedUpgrade.h"
#include "StatComponent.h"
#include "Stat.h"
#include "Player.h"

AttackSpeedUpgrade::AttackSpeedUpgrade(Sprite* icon, const wstring& title, const wstring& description) : Upgrade(icon, title, description)
{
	_maxLevel = 5;
}

AttackSpeedUpgrade::~AttackSpeedUpgrade()
{
}

void AttackSpeedUpgrade::initialize(Player* player)
{
	PlayerDevice::initialize(player);
	_statComponent = player->getComponent<StatComponent>();
}

void AttackSpeedUpgrade::applyUpgrade()
{
	levelUp();
	_statComponent->getStat(L"AttackSpeed")->addModifier(this, _modifyValues[_currentLevel - 1]);
}
