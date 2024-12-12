#include "pch.h"
#include "Player.h"
#include "Window.h"
#include "CCTV.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SpriteRenderer.h"
#include "StatComponent.h"
#include "Stat.h"
#include "UpgradeComponent.h"
#include "UpgradeUI.h"
#include "WindowUI.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "PowerManager.h"
#include "PopupManager.h"
#include "Scene.h"
#include "Sprite.h"
#include "Torch.h"
#include "Camera.h"
#include "Core.h"
#include "Collider.h"
#include "PlayerManager.h"

Player::Player(const Vector2& position, const Vector2& size) : WindowObject(position, size, WINDOW_TYPE::COPY, L"Me.exe")
{
	_window->setCloseable(false);
	_maxHP = 3;
	_hp = _maxHP;
	_window->setPriority(PLAYER_PRIORITY);
	SpriteRenderer* spriteRenderer = addComponent<SpriteRenderer>();
	Sprite* sprite = GET_SINGLETON(ResourceManager)->getSprite(L"Computer");
	spriteRenderer->setSprite(sprite);
	spriteRenderer->setScale({ 3,3 });
	Collider* collider = addComponent<Collider>();
	collider->setSize({ 85,85 });
	_statComponent = addComponent<StatComponent>();
	Stat* damageStat = new Stat(1);
	_statComponent->addStat(L"Damage", damageStat);
	Stat* sizeStat = new Stat(500);
	_statComponent->addStat(L"Size", sizeStat);
	Stat* attackSpeedStat = new Stat(1.5f);
	_statComponent->addStat(L"AttackSpeed", attackSpeedStat);
	Stat* attackStunStat = new Stat(0.f);
	_statComponent->addStat(L"AttackStun", attackStunStat);
	Stat* cameraStunStat = new Stat(1.5f);
	_statComponent->addStat(L"CameraStun", cameraStunStat);
	Stat* cameraDamageStat = new Stat(3);
	_statComponent->addStat(L"CameraDamage", cameraDamageStat);
	Stat* cameraSizeStat = new Stat(500);
	_statComponent->addStat(L"CameraSize", cameraSizeStat);
	Stat* cameraCountStat = new Stat(3);
	_statComponent->addStat(L"CameraCount", cameraCountStat);
	Stat* torchSizeStat = new Stat(300);
	_statComponent->addStat(L"TorchSize", torchSizeStat);
	Stat* torchDamageStat = new Stat(1);
	_statComponent->addStat(L"TorchDamage", torchDamageStat);
	Stat* torchAttackSpeedStat = new Stat(1.2f);
	_statComponent->addStat(L"TorchAttackSpeed", torchAttackSpeedStat);
	GET_SINGLETON(PlayerManager)->setPlayer(this);
	_cctv = new CCTV(_position + Vector2(400, 0), { 500,500 });
	_cctv->initialize(this);
	GET_SINGLETON(EventManager)->createObject(_cctv, LAYER::PLAYER);
	_upgradeComponent = addComponent<UpgradeComponent>();
	_upgradeComponent->initialize();
	_priceMap.insert({ PLAYER_ITEM::CAMERA, 50 });
	_priceMap.insert({ PLAYER_ITEM::TORCH, 40 });
	_priceMap.insert({ PLAYER_ITEM::UPGRADE, 70 });
	_currentItem = PLAYER_ITEM::CAMERA;
}

Player::~Player()
{
}


void Player::update()
{
	if (GET_SINGLETON(Core)->isPaused()) return;
	if (!_isCCTVLocked)
	{
		Vector2 movement = {};
		if (GET_KEY(KEY_TYPE::W))
			movement.y -= 1;
		if (GET_KEY(KEY_TYPE::A))
			movement.x -= 1;
		if (GET_KEY(KEY_TYPE::S))
			movement.y += 1;
		if (GET_KEY(KEY_TYPE::D))
			movement.x += 1;
		movement.Normalize();
		movement *= 300 * DELTATIME;
		_cctv->localMove(movement);
	}
	if (GET_KEYDOWN(KEY_TYPE::NUM_1))
	{
		_currentItem = PLAYER_ITEM::CAMERA;
		OnItemChangeEvent.invoke(_currentItem);
	}
	if (GET_KEYDOWN(KEY_TYPE::NUM_2))
	{
		_currentItem = PLAYER_ITEM::TORCH;
		OnItemChangeEvent.invoke(_currentItem);
	}
	if (GET_KEYDOWN(KEY_TYPE::NUM_3))
	{
		_currentItem = PLAYER_ITEM::UPGRADE;
		OnItemChangeEvent.invoke(_currentItem);
	}
	if (GET_KEYDOWN(KEY_TYPE::SPACE) || GET_KEYDOWN(KEY_TYPE::ENTER))
	{
		switch (_currentItem)
		{
		case PLAYER_ITEM::CAMERA:
		{
			if (!GET_SINGLETON(PowerManager)->trySpendPower(_priceMap[_currentItem]))
			{
				GET_SINGLETON(PopupManager)->popup(L"NotEnoughPower", { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, false);
				return;
			}
			float size = _statComponent->getStat(L"CameraSize")->getValue();
			_isCameraSpawned = false;
			GET_SINGLETON(Core)->OnMessageProcessEvent += [this, size]()
				{
					if (_isCameraSpawned)
					{
						GET_SINGLETON(Core)->OnMessageProcessEvent -= [this]() {};
						return;
					}
					_isCameraSpawned = true;
					Camera* camera = new Camera(_position, { size,size });
					camera->initialize(this);
					GET_SINGLETON(EventManager)->createObject(camera, LAYER::UI);
				};
			_priceMap[_currentItem] += 50;
		}
		break;
		case PLAYER_ITEM::TORCH:
		{
			if (!GET_SINGLETON(PowerManager)->trySpendPower(_priceMap[_currentItem]))
			{
				GET_SINGLETON(PopupManager)->popup(L"NotEnoughPower", { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, false);
				return;
			}
			Vector2 mousePos = Vector2(GET_MOUSEPOS);
			float size = _statComponent->getStat(L"TorchSize")->getValue();
			_isTorchSpawned = false;
			GET_SINGLETON(Core)->OnMessageProcessEvent += [this, size, mousePos]()
				{
					if (_isTorchSpawned)
					{
						GET_SINGLETON(Core)->OnMessageProcessEvent -= [this]() {};
						return;
					}
					_isTorchSpawned = true;
					Torch* torch = new Torch(_position, { size,size });
					torch->initialize(this);
					torch->setup(mousePos);
					GET_SINGLETON(EventManager)->createObject(torch, LAYER::PLAYER);
				};
			_priceMap[_currentItem] += 50;
		}
		break;
		case PLAYER_ITEM::UPGRADE:
		{
			if (!_upgradeComponent->isUpgrading())
			{
				if (!GET_SINGLETON(PowerManager)->trySpendPower(_priceMap[_currentItem]))
				{
					GET_SINGLETON(PopupManager)->popup(L"NotEnoughPower", { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, false);
					return;
				}
				_upgradeComponent->setRandomUpgrade();
				_priceMap[_currentItem] += 70;
			}
		}
		}
		OnItemUseEvent.invoke(_currentItem, _priceMap[_currentItem]);
	}
	if (GET_KEYDOWN(KEY_TYPE::F))
	{
		GET_SINGLETON(PopupManager)->popup(L"PowerGenerator", _position, false);
	}
}

void Player::render(HDC hdc)
{
	componentRender(hdc);
}

void Player::modifyHP(int value)
{
	int prev = _hp;
	_hp += value;
	if (value < 0)
	{
		GET_SINGLETON(ResourceManager)->play(L"PlayerHit");
	}
	OnHPChangeEvent.invoke(prev, _hp);
}
