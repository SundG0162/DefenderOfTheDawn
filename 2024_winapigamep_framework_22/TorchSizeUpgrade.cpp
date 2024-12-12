#include "pch.h"
#include "TorchSizeUpgrade.h"
#include "StatComponent.h"
#include "Stat.h"
#include "Player.h"

TorchSizeUpgrade::TorchSizeUpgrade(Sprite* icon, const wstring& title, const wstring& description) : Upgrade(icon, title, description)
{
	_maxLevel = 2;
}

TorchSizeUpgrade::~TorchSizeUpgrade()
{
}

void TorchSizeUpgrade::initialize(Player* player)
{
	PlayerDevice::initialize(player);
	_statComponent = player->getComponent<StatComponent>();
}

void TorchSizeUpgrade::applyUpgrade()
{
	levelUp();
	_statComponent->getStat(L"TorchSize")->addModifier(this, _modifyValues[_currentLevel - 1]);
}
