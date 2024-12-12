#include "pch.h"
#include "SkillEnemy.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "StatComponent.h"
#include "Stat.h"
#include "Collider.h"

SkillEnemy::SkillEnemy()
{
	stat->addStat(L"moveSpeed", new Stat(50.f));
	stat->addStat(L"CoolTime", new Stat(3.f));
	stat->addStat(L"SkilTime", new Stat(0.1f));
}

SkillEnemy::~SkillEnemy()
{
}

void SkillEnemy::update()
{
	_skillcoolTime = stat->getStat(L"CoolTime")->getValue();
	_skillTime = stat->getStat(L"SkilTime")->getValue();

	if (_skilluseTime > 0.f)
	{
		_skilluseTime -= DELTATIME;
		updateSkill();
	}
	else
	{
		if (_currentTime > _skillcoolTime)
		{
			_currentTime = 0.f;
			_skilluseTime = _skillTime;
			cout << "skillusetime setto " << _skilluseTime;
			startSkill();
			_isUsingSkillOver = true;
		}
		else if(_isUsingSkillOver)
		{
			endSkill();
			_isUsingSkillOver = false;
		}
		_currentTime += DELTATIME;
	}
	Enemy::update();

}

void SkillEnemy::render(HDC hdc)
{
	Enemy::render(hdc);
}

void SkillEnemy::useSkill()
{
}

void SkillEnemy::startSkill()
{
}

void SkillEnemy::updateSkill()
{
}

void SkillEnemy::endSkill()
{
}

