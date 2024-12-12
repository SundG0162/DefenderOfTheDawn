#include "pch.h"
#include "InvincibleEnemy.h"
#include "ResourceManager.h"
#include "AnimationClip.h"
#include "Animator.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "StatComponent.h"
#include "Stat.h"
#include "Collider.h"

InvincibleEnemy::InvincibleEnemy()
{
	SpriteRenderer* renderer = addComponent<SpriteRenderer>();
	renderer->setScale({ 2,2 });
	Texture* tex = GET_SINGLETON(ResourceManager)->getTexture(L"EnemySheet");
	Animator* anim = getComponent<Animator>();

	{
		auto vecsprite = utils::SpriteParser::textureToSprites(tex, { 0, 32 * 2 }, { 32,32 }, 6);
		anim->createAnimation(L"invincibleEnd", vecsprite, 0.05f * 6);
	}
	{
		auto vecsprite = utils::SpriteParser::textureToSprites(tex, { 0, 32 * 2 }, { 32,32 }, 6);
		reverse(vecsprite.begin(), vecsprite.end());
		anim->createAnimation(L"invincibleStart", vecsprite, 0.05f * 6);
	}
	{
		auto vecsprite = utils::SpriteParser::textureToSprites(tex, { 0, 32 * 3 }, { 32,32 }, 2);
		anim->createAnimation(L"imove", vecsprite, 0.2f * 2);
	}
	anim->playAnimation(L"imove", true);
	anim->findAnimation(L"invincibleEnd")->OnAnimationEndEvent += [this]() 
		{
			getComponent<Animator>()->playAnimation(L"imove", true);
			getComponent<Collider>()->setOffset({ 0,0 });
			stat->getStat(L"moveSpeed")->removeModifier(this);
		};

	anim->findAnimation(L"invincibleStart")->OnAnimationEndEvent += [this]()
		{
			getComponent<Collider>()->setOffset({ 5555,5555 });
			stat->getStat(L"moveSpeed")->addModifier(this, -40);
		};
	

	stat->getStat(L"moveSpeed")->setValue(50.f);
	stat->getStat(L"CoolTime")->setValue(999999.f);
	stat->getStat(L"SkilTime")->setValue(3.f);

	OnAttackEvent += [this]()
		{
			stat->getStat(L"CoolTime")->addModifier(this, -999998.f);
			useSkill();
		};
}

InvincibleEnemy::~InvincibleEnemy()
{
}

void InvincibleEnemy::update()
{
	Super::update();
}

void InvincibleEnemy::render(HDC hdc)
{
	Super::render(hdc);
}

void InvincibleEnemy::startSkill()
{
	
}

void InvincibleEnemy::updateSkill()
{
}

void InvincibleEnemy::endSkill()
{
	cout << "endskill";
	useSkill();
}

void InvincibleEnemy::useSkill()
{
	_isUsing = !_isUsing;
	if (_isUsing)
	{
		getComponent<Animator>()->playAnimation(L"invincibleStart", false);
	}
	else
	{
		getComponent<Animator>()->playAnimation(L"invincibleEnd", false);
		stat->getStat(L"CoolTime")->removeModifier(this);
	}
}
