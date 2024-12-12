#pragma once
#include "Object.h"
#include "Action.h"
class WindowObject;
class StatComponent;
class Enemy :
    public Object
{
public:
    Enemy();
    virtual ~Enemy();
    // Inherited via Object
    virtual void update() override;
    virtual void render(HDC hdc) override;

    void Move();
    void DoMove(Vector2& vec);
    void GetDamage(int damage);
    void GetStunned(float time);

    void SetRandomPos() { setPosition((utils::ExMath::getRandomVector() + Vector2(0.5f, 0.5f)) * Vector2(SCREEN_WIDTH, SCREEN_HEIGHT)); }
    void Setup();
    void SetTarget(Object* target) { _target = target; }

public:
    Action<> OnAttackEvent;
protected:
    StatComponent* stat;
    Vector2 _moveVector;
    //Vector2 posScale = { SCREEN_WIDTH/2, SCREEN_HEIGHT/2 };
    int _maxHealth;
    int _curHealth;
    Object* _target;
    Vector2 toTarget;
private:
    bool _isMovable;
    float _whiteTimer;
    float _stunTime;
};

