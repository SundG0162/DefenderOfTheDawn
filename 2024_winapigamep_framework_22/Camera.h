#pragma once
#include "CaptureObject.h"
#include "PlayerDevice.h"
class BarUI;
class Enemy;
class FadeInOut;
class Collider;
class Camera : public CaptureObject, public PlayerDevice
{
public:
	Camera(const Vector2& position, const Vector2& size);
	~Camera();
public:
	void initialize(Player* player) override;
	void update() override;
	void render(HDC hdc) override;
public:
	void handleOnWindowMove(const Vector2& prev, const Vector2& current);
private:
	FadeInOut* _fadeOut;
	BarUI* _bar;
	int _counter;
	int _maxCount;
	int _attackDamage = 3;
	float _stunTime;
	float _timer = 0.f;
};