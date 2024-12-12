#include "pch.h"
#include "Torch.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "BarUI.h"
#include "Window.h"
#include "WindowUI.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "Player.h"
#include "Animator.h"
#include "Core.h"
#include "SpriteRenderer.h"
#include "StatComponent.h"
#include "Stat.h"
#include "Enemy.h"

Torch::Torch(const Vector2& position, const Vector2& size) : CaptureObject(position, size, WINDOW_TYPE::COPY, L"Torch.exe")
{
	_duration = 10.f;
	_attackTimer = 0.f;
	_timer = 0.f;
	_settingUp = true;
	_bar = nullptr;

	Texture* texture = GET_SINGLETON(ResourceManager)->getTexture(L"Torch");
	SpriteRenderer* renderer = addComponent<SpriteRenderer>();
	RECT rect = { 0,0,_size.x,_size.y };
	GetWindowRect(_window->getHWnd(), &rect);
	Vector2 offset = utils::CoordinateSync::nonClientToClient(rect, _position) - _position;
	renderer->setScale({ 5,5 });
	renderer->setOffset(offset);
	Animator* animator = addComponent<Animator>();
	vector<Sprite*> sprites = utils::SpriteParser::textureToSprites(texture, { 0,0 }, { 32,32 }, { 32,0 });
	animator->createAnimation(L"Idle", sprites, 0.5f);
	animator->playAnimation(L"Idle", true);
	_window->setPriority(CCTV_PRIORITY - 1);
}

Torch::~Torch()
{
	
}

void Torch::initialize(Player* player)
{
	PlayerDevice::initialize(player);
	_statComponent = player->getComponent<StatComponent>();
}

void Torch::update()
{
	CaptureObject::update();
	_timer += DELTATIME;
	if (_settingUp)
	{
		Vector2 prevPos = _position;
		_position.x = std::lerp(_startPos.x, _goalPos.x, utils::Ease::outCubic(_timer));
		_position.y = std::lerp(_startPos.y, _goalPos.y, utils::Ease::outCubic(_timer));
		_window->moveWindow(_position);
		if (_timer > 1)
		{
			_timer = 0.f;
			_settingUp = false;
			GET_SINGLETON(ResourceManager)->play(L"TorchStart");
			GET_SINGLETON(Core)->OnMessageProcessEvent += [this]()
				{
					GET_SINGLETON(Core)->OnMessageProcessEvent -= [this]() {};
					_bar = new WindowUI({ _position.x - 30, _position.y - _size.y / 3 }, { 240,30 }, WINDOW_TYPE::NEW, L"Ember.exe");
					BarUI* bar = new BarUI({ _bar->getSize().x / 2, _bar->getSize().y / 2 }, { 240,30 });
					_bar->getWindow()->setMoveable(true);
					_bar->getWindow()->setCloseable(true);
					_bar->setUI(bar);
					_bar->getWindow()->OnWindowCloseEvent += [this]() {_bar = nullptr; };
					GET_SINGLETON(EventManager)->createObject(_bar, LAYER::UI);
				};
		}
		return;
	}
	if (!_window->isTweening())
		tryAttack();
	float ratio = 1 - _timer / _duration;
	if (_bar != nullptr && !_bar->isDead())
		_bar->getUI<BarUI>()->setFillAmount(ratio);
	if (_timer >= _duration && !_window->isTweening())
	{
		_window->closeTween(0.5f);
		if (_bar != nullptr && !_bar->isDead())
			_bar->getWindow()->closeTween(0);
		_window->OnTweenEndEvent += [this]()
			{
				if (_bar != nullptr && _bar->isDead())
				{
					GET_SINGLETON(EventManager)->deleteObject(_bar);
					_bar = nullptr;
				}
				GET_SINGLETON(EventManager)->deleteObject(this);
			};
	}
}

void Torch::render(HDC hdc)
{
	componentRender(hdc);
}

void Torch::tryAttack()
{
	_attackTimer += DELTATIME;
	if (_attackTimer >= _statComponent->getStat(L"TorchAttackSpeed")->getValue())
	{
		_attackTimer = 0.f;
		attack();
	}
}

void Torch::attack()
{
	if (_targets.size() > 0)
		GET_SINGLETON(ResourceManager)->play(L"EnemyHit");
	int damage = _statComponent->getStat(L"TorchDamage")->getValue();
	for (Enemy* enemy : _targets)
	{
		enemy->GetDamage(damage);
	}
}

void Torch::setup(const Vector2& position)
{
	_goalPos = position;
	_startPos = _position;
	_settingUp = true;
}
