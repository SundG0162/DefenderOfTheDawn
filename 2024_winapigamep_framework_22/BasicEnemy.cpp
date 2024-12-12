#include "pch.h"
#include "BasicEnemy.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "StatComponent.h"
#include "Stat.h"

BasicEnemy::BasicEnemy()
{
	getComponent<StatComponent>()->getStat(L"moveSpeed")->setValue(50.f);
}

BasicEnemy::~BasicEnemy()
{
}

void BasicEnemy::update()
{
	Super::update();
}

void BasicEnemy::render(HDC hdc)
{
	Super::render(hdc);
}