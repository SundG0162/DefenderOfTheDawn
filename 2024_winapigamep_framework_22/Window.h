#pragma once
#include "Action.h"
enum class TWEEN_TYPE
{
	HORIZON,
	VERTICAL
};
class Window
{
public:
	Window(const Vector2& position, const Vector2& size, const wstring& name = L"");
	virtual ~Window();
public:
	virtual void update();
	virtual void render(HDC hdc) abstract;
public:
	static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT handleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	void openTween(float delayTime = 1.f, float speed = 1.f, TWEEN_TYPE type = TWEEN_TYPE::VERTICAL);
	void closeTween(float delayTime = 1.f, float speed = 1.f, TWEEN_TYPE type = TWEEN_TYPE::VERTICAL);
	virtual void closeWindow();
	virtual void openWindow();
	void close();
	void moveWindow(const Vector2& pos);
public:
	void setWindowName(const wstring& name);
	void setPosition(const Vector2& position) { _position = position; }
	const Vector2& getPosition() { return _position; }
	void setSize(const Vector2& size) { _size = size; }
	const Vector2& getSize() { return _size; }
	const HWND& getHWnd() { return _hWnd; }
	void setCloseable(bool closeable) { _closeable = closeable; }
	const bool& getCloseable() { return _closeable; }
	void setMoveable(bool moveable) { _moveable = moveable; }
	const bool& getMoveable() { return _moveable; }
	void setDead() { _isDead = true; }
	void setPriority(int priority);
	const int& getPriority() { return _priority; }
	const bool& isDead() { return _isDead; }
	const bool& isTweening() { return !_isTweenEnd; }
	const bool& isClosed() { return _isClosed; }
public:
	Action<const Vector2&, const Vector2&> OnWindowMoveEvent;
	Action<> OnTweenEndEvent;
	Action<> OnWindowCloseEvent;
	Action<> OnTryWindowCloseEvent;
	Action<> OnWindowOpenEvent;
protected:
	HWND _hWnd;
	HDC _hMainDC;
	wstring _name;
	Vector2 _position;
	Vector2 _size;
	Vector2 _leftTopPosition;
	float _speed = 1.f;
	float _timer = 0.f;
	float _delayTime = 0.f;
	Vector2 _goalSize;
	Vector2 _startSize;
	TWEEN_TYPE _tweenType;
	bool _moveable = false;
	bool _isTweenEnd = true;
	bool _closeable = true;
	bool _isDead = false;
	bool _isClosed = false;
	int _priority = 0;
};