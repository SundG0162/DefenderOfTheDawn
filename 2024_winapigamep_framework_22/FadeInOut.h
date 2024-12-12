#pragma once
#include "Object.h"
enum class FADE_TYPE
{
	FADE_IN,
	FADE_OUT
};
class FadeInOut : public Object
{
public:
	FadeInOut(const Vector2& position, const Vector2& size);
	~FadeInOut();
public:
	void init(const float& fadeTime, const FADE_TYPE& type);
	void update() override;
	void render(HDC hdc) override;
private:
	BLENDFUNCTION _blendFunction;
	FADE_TYPE _type;
	HDC _hDC;
	HBITMAP _hBitmap;
	float _timer;
	float _fadeTime;
};

