#include "pch.h"
#include "SizeUpgrade.h"
#include "StatComponent.h"
#include "Stat.h"
#include "Player.h"

SizeUpgrade::SizeUpgrade(Sprite* icon, const wstring& title, const wstring& description) : Upgrade(icon, title, description)
{
	_maxLevel = 5;
}

SizeUpgrade::~SizeUpgrade()
{
}

void SizeUpgrade::initialize(Player* player)
{
	PlayerDevice::initialize(player);
	_statComponent = player->getComponent<StatComponent>();
}

void SizeUpgrade::applyUpgrade()
{
	levelUp();
	_statComponent->getStat(L"Size")->addModifier(this, _modifyValues[_currentLevel - 1]);
}
