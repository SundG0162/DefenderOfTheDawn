#include "pch.h"
#include "FadeInOut.h"
#include "Core.h"
#include "TimeManager.h"

FadeInOut::FadeInOut(const Vector2& position, const Vector2& size) : Object()
{
	_position = position;
	_size = size;
	_timer = 0.f;
	_blendFunction = { AC_SRC_OVER, 0, 0, AC_SRC_OVER };
	HDC hBackDC = GET_SINGLETON(Core)->getBackDC();
	_hDC = CreateCompatibleDC(hBackDC);
	_hBitmap = CreateCompatibleBitmap(hBackDC, size.x, size.y);
	SelectObject(_hDC, _hBitmap);
	PatBlt(_hDC, 0, 0, size.x, size.y, WHITENESS);
	RECT windowRect = {
		(LONG)_position.x,
		(LONG)_position.y,
		(LONG)(_position.x + _size.x),
		(LONG)(_position.y + _size.y)
	};
	RECT clientRect = windowRect;
	AdjustWindowRect(&clientRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, FALSE);
	Vector2 fixedPosition;
	fixedPosition.x = _position.x - (windowRect.left - clientRect.left);
	fixedPosition.y = _position.y - (windowRect.top - clientRect.top);
	Vector2 fixedSize;
	fixedSize.x = _size.x - (windowRect.right - windowRect.left - _size.x);
	fixedSize.y = _size.y - (windowRect.bottom - windowRect.top - _size.y);
	_position = fixedPosition;
	_size = fixedSize;
}

FadeInOut::~FadeInOut()
{
	DeleteObject(_hBitmap);
	DeleteDC(_hDC);
}

void FadeInOut::init(const float& fadeTime, const FADE_TYPE& type)
{
	_fadeTime = fadeTime;
	_timer = fadeTime;
	_type = type;
	_blendFunction.SourceConstantAlpha = type == FADE_TYPE::FADE_IN ? 0.f : 1.f;
}

void FadeInOut::update()
{
	if (_timer > 0)
	{
		_timer -= DELTATIME;
		float alpha = 0.f;
		if (_type == FADE_TYPE::FADE_OUT)
			alpha = _timer / _fadeTime;  // 1에서 0으로 감소
		else
			alpha = 1.0f - (_timer / _fadeTime);  // 0에서 1로 증가
		_blendFunction.SourceConstantAlpha = alpha * 255.f;
	}
}

void FadeInOut::render(HDC hdc)
{
	Vector2 leftTop = GET_LEFTTOPPOS(_position, _size);
	AlphaBlend(hdc, leftTop.x, leftTop.y, _size.x, _size.y, _hDC, 0, 0, _size.x, _size.y, _blendFunction);
}
