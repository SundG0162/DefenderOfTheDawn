#pragma once
#include "SkillEnemy.h"
class InvincibleEnemy :
    public SkillEnemy
{
    using Super = SkillEnemy;
public:
    InvincibleEnemy();
    ~InvincibleEnemy();

    virtual void update() override;
    virtual void render(HDC hdc) override;
    virtual void startSkill();
    virtual void updateSkill();
    virtual void endSkill();
    void useSkill();    

    void SetSkillUseTime(float time) { _skillTime = time; }
    void SetSkillCoolTime(float time) { _skillcoolTime = time; }
private:
    bool _isUsing = false;
};

