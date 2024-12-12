#include "pch.h"
#include "TorchAttackSpeedUpgrade.h"
#include "StatComponent.h"
#include "Stat.h"
#include "Player.h"

TorchAttackSpeedUpgrade::TorchAttackSpeedUpgrade(Sprite* icon, const wstring& title, const wstring& description) : Upgrade(icon, title, description)
{
	_maxLevel = 2;
}

TorchAttackSpeedUpgrade::~TorchAttackSpeedUpgrade()
{
}

void TorchAttackSpeedUpgrade::initialize(Player* player)
{
	PlayerDevice::initialize(player);
	_statComponent = player->getComponent<StatComponent>();
}

void TorchAttackSpeedUpgrade::applyUpgrade()
{
	levelUp();
	_statComponent->getStat(L"TorchAttackSpeed")->addModifier(this, _modifyValues[_currentLevel - 1]);
}
