#pragma once
#include "Enemy.h"
class SkillEnemy :
    public Enemy
{
    using Super = Enemy;
public:
    SkillEnemy();
    virtual ~SkillEnemy();

    virtual void update() override;
    virtual void render(HDC hdc) override;
    void useSkill();
    virtual void startSkill();
    virtual void updateSkill();
    virtual void endSkill();

protected:
    float _skillcoolTime = 0.f;
    float _currentTime = 0.f;
    float _skillTime = 0.f;
    float _skilluseTime=0.f;
    bool _isUsingSkillOver=false;
};

