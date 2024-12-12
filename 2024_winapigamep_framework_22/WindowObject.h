#pragma once
#include "Object.h"
class Window;
class WindowObject : public Object
{
public:
	WindowObject(const Vector2& position, const Vector2& size, const WINDOW_TYPE& type, const wstring& name = L"");
	virtual ~WindowObject();
public:
	void openTween(float delayTime = 1.f);
public:
	Window* getWindow() { return _window; }
	const WINDOW_TYPE& getType() { return _type; }
protected:
	WINDOW_TYPE _type;
	Window* _window;
};

