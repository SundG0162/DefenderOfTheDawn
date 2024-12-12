#pragma once
#include "CaptureObject.h"
#include "PlayerDevice.h"
class WindowUI;
class Player;
class StatComponent;
class Torch : public CaptureObject, public PlayerDevice
{
public:
	Torch(const Vector2& position, const Vector2& size);
	~Torch();
public:
	void initialize(Player* player) override;
	void update() override;
	void render(HDC hdc) override;
public:
	void tryAttack();
	void attack();
	void setup(const Vector2& position);
	void setDuration(float duration) { _duration = duration; }
private:
	StatComponent* _statComponent;
	Vector2 _startPos;
	Vector2 _goalPos;
	bool _settingUp;
	WindowUI* _bar;
	float _duration;
	float _attackTimer;
	float _timer;
};