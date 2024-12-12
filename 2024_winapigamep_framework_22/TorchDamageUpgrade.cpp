#include "pch.h"
#include "TorchDamageUpgrade.h"
#include "StatComponent.h"
#include "Stat.h"
#include "Player.h"

TorchDamageUpgrade::TorchDamageUpgrade(Sprite* icon, const wstring& title, const wstring& description) : Upgrade(icon, title, description)
{
	_maxLevel = 2;
}

TorchDamageUpgrade::~TorchDamageUpgrade()
{
}

void TorchDamageUpgrade::initialize(Player* player)
{
	PlayerDevice::initialize(player);
	_statComponent = player->getComponent<StatComponent>();
}

void TorchDamageUpgrade::applyUpgrade()
{
	levelUp();
	_statComponent->getStat(L"TorchDamage")->addModifier(this, _modifyValues[_currentLevel - 1]);
}
