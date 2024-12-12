#pragma once
#include "CaptureObject.h"
#include "PlayerDevice.h"
class Collider;
class StatComponent;
class Enemy;
class CCTV : public CaptureObject, public PlayerDevice
{
public:
	CCTV(const Vector2& position, const Vector2& size);
	~CCTV();
public:	
	void initialize(Player* player) override;
	void update() override;
	void render(HDC hdc) override;
public:
	void localMove(const Vector2& move);
	void tryAttack();
	void attack();
public:
	void handleOnSizeStatChange(float prev, float current);
private:
	StatComponent* _statComponent;
	int _attackDamage = 1;
	float _attackTimer = 0.f;
};