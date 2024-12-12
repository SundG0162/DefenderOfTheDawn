#include "pch.h"
#include "SpinEnemy.h"
#include "SpriteRenderer.h"
#include "StatComponent.h"
#include "Stat.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Stat.h"
#include "StatComponent.h"
#include "Animator.h"

SpinEnemy::SpinEnemy()
{
	Animator* animator = getComponent<Animator>();
	Texture* tex = GET_SINGLETON(ResourceManager)->getTexture(L"EnemySheet");
	vector<Sprite*> sprites = utils::SpriteParser::textureToSprites(tex, { 0,32 }, { 32,32 }, 4);
	animator->createAnimation(L"SpinEnemyIdle", sprites, 1.f);
	animator->playAnimation(L"SpinEnemyIdle", true);
	stat->addStat(L"DashRatio", new Stat(0.3f));

	stat->addStat(L"SpinRatio", new Stat(1.5f));
	stat->getStat(L"moveSpeed")->setValue(150.f);
}

SpinEnemy::~SpinEnemy()
{
}

void SpinEnemy::update()
{
	Super::update();
	if (toTarget.Length() < 50) return;
	utils::ExMath::rotateVector(_moveVector, 90);
	_moveVector = _moveVector * getComponent<StatComponent>()->getStat(L"SpinRatio")->getValue();
	DoMove(_moveVector);
	_moveVector = _moveVector / getComponent<StatComponent>()->getStat(L"SpinRatio")->getValue();
}

void SpinEnemy::render(HDC hdc)
{
	Super::render(hdc);
}
