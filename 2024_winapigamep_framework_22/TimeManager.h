#pragma once
class TimeManager
{
	DECLARE_SINGLETON(TimeManager);
public:
	void init();
	void update();
public:
	void setTimeScale(float timeScale) { _timeScale = timeScale; }
	const int& getTimeScale() { return _timeScale; }
	const float& getDeltaTime() const { return _deltaTime; }
private:
	float _timeScale = 1.f;
	LARGE_INTEGER _prevCount = {};
	LARGE_INTEGER _currentCount = {};
	LARGE_INTEGER _frequency = {};
	float		  _deltaTime = 0.f;
	UINT		  _fps = 0;
	UINT		  _frameCount = 0;
	float		  _frameTime = 0.f;
};

