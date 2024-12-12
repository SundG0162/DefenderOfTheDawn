#include "pch.h"
#include "CCTVStunUpgrade.h"
#include "StatComponent.h"
#include "Stat.h"
#include "Player.h"

CCTVStunUpgrade::CCTVStunUpgrade(Sprite* icon, const wstring& title, const wstring& description) : Upgrade(icon, title, description)
{
	_maxLevel = 1;
}

CCTVStunUpgrade::~CCTVStunUpgrade()
{
}

void CCTVStunUpgrade::initialize(Player* player)
{
	PlayerDevice::initialize(player);
	_statComponent = player->getComponent<StatComponent>();
}

void CCTVStunUpgrade::applyUpgrade()
{
	levelUp();
	_statComponent->getStat(L"AttackStun")->addModifier(this, _modifyValues[_currentLevel - 1]);
}
