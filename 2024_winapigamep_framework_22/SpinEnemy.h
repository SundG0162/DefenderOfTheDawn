#pragma once
#include "Enemy.h"
class SpinEnemy :
    public Enemy
{
    using Super = Enemy;
public:
    SpinEnemy();
    SpinEnemy(Object* target);
    ~SpinEnemy();
    virtual void update() override;
    virtual void render(HDC hdc) override;
};

