#include "pch.h"
#include "Enemy.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "Collider.h"
#include "SpriteRenderer.h"
#include "Sprite.h"
#include "StatComponent.h"
#include "PowerManager.h"
#include "ResourceManager.h"
#include "ResultManager.h"
#include "Animator.h"
#include "Stat.h"
#include "Player.h"
#include "ExplodeEffect.h"

Enemy::Enemy()
	: _moveVector(0.f, 0.f)
	, _maxHealth(5.f)
	, _curHealth(5.f)
	, _isMovable(true)
	, _stunTime(0.f)
	, _target(nullptr)
{
	Collider* collider = addComponent<Collider>();
	collider->OnCollisionEnterEvent += [this](Collider* other)
		{
			Object* obj = other->getOwner();
			Player* player = dynamic_cast<Player*>(obj);
			if (player)
			{
				player->modifyHP(-1);
				GET_SINGLETON(PowerManager)->
					modifyPower(getComponent<StatComponent>()->
						getStat(L"powerEarnOnDead")->getValue());
				_isDead = true;
				GET_SINGLETON(ResultManager)->modifyTotalCaughtEnemy(1);
				GET_SINGLETON(EventManager)->deleteObject(this);

			}
		};
	SetRandomPos();
	stat = addComponent<StatComponent>();
	stat->addStat(L"moveSpeed", new Stat(20.f));
	stat->addStat(L"maxHealth", new Stat(2.f));
	//stat->addStat(L"powerEarnOnDead", new Stat(10.f));
	Setup();

	SpriteRenderer* renderer = addComponent<SpriteRenderer>();
	renderer->setScale({ 2,2 });
	Texture* tex = GET_SINGLETON(ResourceManager)->getTexture(L"EnemySheet");
	Animator* anim = addComponent<Animator>();

	{
		auto vecsprite = utils::SpriteParser::textureToSprites(tex, { 0, 32 * 5 }, { 32,32 }, 4);
		anim->createAnimation(L"move", vecsprite, 0.4);
	}
	anim->playAnimation(L"move", true);
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
	componentUpdate();
	Move();
	if (_whiteTimer > 0)
	{
		_whiteTimer -= DELTATIME;
		if (_whiteTimer <= 0)
		{
			getComponent<SpriteRenderer>()->setWhiteness(false);
		}
	}
}

void Enemy::render(HDC hdc)
{
	componentRender(hdc);
}

void Enemy::Move()
{
	{
		Vector2 targetpos = _target->getPosition();
		toTarget = targetpos - _position;
	}
	Vector2 direction = toTarget;
	direction.Normalize();
	_moveVector = direction * (stat->getStat(L"moveSpeed")->getValue() * DELTATIME);
	DoMove(_moveVector);
}

void Enemy::DoMove(Vector2& vec)
{
	if (!_isMovable)
	{
		_stunTime -= DELTATIME;
		if (_stunTime < 0) _isMovable = true;
		return;
	}
	_position = vec + _position;
}


void Enemy::GetDamage(int damage)
{
	_curHealth -= damage;
	OnAttackEvent.invoke();
	getComponent<SpriteRenderer>()->setWhiteness(true);
	_whiteTimer = 0.2f;
	GET_SINGLETON(ResourceManager)->play(L"EnemyHit", SOUND_CHANNEL::HIT);
	GET_SINGLETON(ResultManager)->modifyTotalDamage(damage);
	if (_curHealth <= 0)
	{
		GET_SINGLETON(PowerManager)->
			modifyPower(getComponent<StatComponent>()->
				getStat(L"powerEarnOnDead")->getValue());
		ExplodeEffect* effect = new ExplodeEffect();
		effect->setPosition(_position);
		effect->play();
		_isDead = true;
		GET_SINGLETON(ResourceManager)->play(L"Die", SOUND_CHANNEL::DEAD);
		GET_SINGLETON(ResultManager)->modifyTotalCaughtEnemy(1);
		GET_SINGLETON(EventManager)->deleteObject(this);
	}
}

void Enemy::GetStunned(float time)
{
	_stunTime = max(_stunTime, time);
	_isMovable = false;
}

void Enemy::Setup()
{
	SetRandomPos();
	_maxHealth = getComponent<StatComponent>()->getStat(L"maxHealth")->getValue();
	_curHealth = _maxHealth;
}

