#include "pch.h"
#include "DashEnemy.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "StatComponent.h"
#include "Animator.h"
#include "Stat.h"


DashEnemy::DashEnemy()
{
	Animator* animator = getComponent<Animator>();
	Texture* tex = GET_SINGLETON(ResourceManager)->getTexture(L"EnemySheet");
	vector<Sprite*> sprites = utils::SpriteParser::textureToSprites(tex, { 0,32*4 }, { 32,32 }, 4);
	animator->createAnimation(L"DashEnemyIdle", sprites, 0.5f);
	animator->playAnimation(L"DashEnemyIdle", true);
	stat->addStat(L"DashRatio", new Stat(0.3f));

	stat->getStat(L"moveSpeed")->setValue(20.f);
	stat->getStat(L"CoolTime")->setValue(5.f);
	stat->getStat(L"SkilTime")->setValue(0.1f);
}

DashEnemy::~DashEnemy()
{
}

void DashEnemy::update()
{
	Super::update();
}

void DashEnemy::render(HDC hdc)
{
	Super::render(hdc);
}

void DashEnemy::startSkill()
{
	if (toTarget.Length() < 50) return;
	Vector2 dashLength = toTarget * stat->getStat(L"DashRatio")->getValue();

	DoMove(dashLength);

}

void DashEnemy::updateSkill()
{
	//cout << "updatedash" << std::endl;
}

void DashEnemy::endSkill()
{
}
