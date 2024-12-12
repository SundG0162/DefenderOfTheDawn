#include "pch.h"
#include "CCTV.h"
#include "Window.h"
#include "Collider.h"
#include "Enemy.h"
#include "Player.h"
#include "TimeManager.h"
#include "StatComponent.h"
#include "WindowManager.h"
#include "ResourceManager.h"
#include "PowerManager.h"
#include "Stat.h"

CCTV::CCTV(const Vector2& position, const Vector2& size) : CaptureObject(position, size, WINDOW_TYPE::COPY, L"CCTV.exe")
{
	_collider->setFollowing(false);
	_window->setPriority(CCTV_PRIORITY);
}

CCTV::~CCTV()
{
	_statComponent->getStat(L"Size")->OnValueChangeEvent -=
		[this](float prev, float current)
		{ this->handleOnSizeStatChange(prev, current); };
}

void CCTV::initialize(Player* player)
{
	PlayerDevice::initialize(player);
	_statComponent = player->getComponent<StatComponent>();
	_statComponent->getStat(L"Size")->OnValueChangeEvent +=
		[this](float prev, float current)
		{ this->handleOnSizeStatChange(prev, current); };
}

void CCTV::update()
{
	CaptureObject::update();
	RECT rect = { 0,0,_size.x,_size.y };
	GetWindowRect(_window->getHWnd(), &rect);
	_collider->setPosition(utils::CoordinateSync::nonClientToClient(rect, _position));
	tryAttack();
}

void CCTV::render(HDC hdc)
{
	componentRender(hdc);
}

void CCTV::localMove(const Vector2& move)
{
	_position += move;
	_window->moveWindow(_position);
}

void CCTV::tryAttack()
{
	_attackTimer += DELTATIME;
	if (_attackTimer >= _statComponent->getStat(L"AttackSpeed")->getValue())
	{
		_attackTimer = 0.f;
		attack();
	}
}

void CCTV::attack()
{
	if (_targets.size() > 0)
	{
		if (GET_SINGLETON(PowerManager)->trySpendPower(5))
		{
			if (_targets.size() > 0)
				GET_SINGLETON(ResourceManager)->play(L"EnemyHit");
			int damage = _statComponent->getStat(L"Damage")->getValue();
			float stunTime = _statComponent->getStat(L"AttackStun")->getValue();
			for (Enemy* enemy : _targets)
			{
				enemy->GetDamage(damage);
				enemy->GetStunned(stunTime);
			}
		}
	}

}

void CCTV::handleOnSizeStatChange(float prev, float current)
{
	_window->setSize({ current, current });
	_size = { current, current };
	_collider->setSize(_size);
}
