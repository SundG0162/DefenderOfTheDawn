#include "pch.h"
#include "BaseWindow.h"
#include "Window.h"
#include "Core.h"
#include "TimeManager.h"
#include "WindowManager.h"
#include "EventManager.h"
#include "Core.h"
#include "ResourceManager.h"

Window::Window(const Vector2& position, const Vector2& size, const wstring& name)
	: _hWnd(nullptr)
	, _hMainDC(nullptr)
	, _position(position)
	, _size(size)
	, _name(name)
{
	WNDCLASS wc = { 0 }; // 구조체를 0으로 초기화

	wc.lpfnWndProc = Window::wndProc; // 윈도우 프로시저 함수 설정
	wc.hInstance = GET_SINGLETON(Core)->getHInstance(); // 인스턴스 핸들 설정
	wc.lpszClassName = L"엄준식"; // 클래스 이름 설정
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 배경색 설정

	RegisterClass(&wc);

	RECT windowRect = { 0, 0, size.x, size.y };
	AdjustWindowRect(&windowRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, FALSE);

	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;
	Vector2 fixedSize = { width,height };

	Vector2 fixedPos = GET_LEFTTOPPOS(position, Vector2(fixedSize.x, fixedSize.y));

	_hWnd = CreateWindowEx(
		0,
		L"엄준식",
		name.c_str(),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		fixedPos.x, fixedPos.y,
		fixedSize.x, fixedSize.y,
		NULL,
		NULL,
		GET_SINGLETON(Core)->getHInstance(),
		this
	);
	_leftTopPosition = fixedPos;
	ShowWindow(_hWnd, SW_SHOW);
	_hMainDC = GetDC(_hWnd);
	_size = fixedSize;
	GET_SINGLETON(WindowManager)->addWindow(this);
}

Window::~Window()
{

}


LRESULT CALLBACK Window::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Window* window = nullptr;

	if (message == WM_NCCREATE)
	{
		CREATESTRUCT* create = reinterpret_cast<CREATESTRUCT*>(lParam);
		window = reinterpret_cast<Window*>(create->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
	}
	else
		window = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	if (window != nullptr && !window->isDead() && !window->isClosed())
		return window->handleMessage(hWnd, message, wParam, lParam);
	else
		return DefWindowProc(hWnd, message, wParam, lParam);
}
LRESULT Window::handleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SYSCOMMAND:
	{
		if (!_moveable)
		{
			switch (wParam & 0xFFF0)
			{
			case SC_MOVE:
			case SC_SIZE:
			case SC_MAXIMIZE:
				return 0;
			}
		}
		else
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_MOVING:
	{
		RECT* rect = (RECT*)lParam;  // 드래그 중인 창의 새 위치
		int posX = rect->left + (rect->right - rect->left) / 2;
		int posY = rect->top + (rect->bottom - rect->top) / 2;
		Vector2 currentPosition = { (float)posX, (float)posY };
		OnWindowMoveEvent.invoke(_position, currentPosition);
		_position = currentPosition;
	}
	break;
	case WM_CLOSE:
	{
		GET_SINGLETON(ResourceManager)->play(L"Snap");
		if (_closeable)
		{
			OnWindowCloseEvent.invoke();
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		else
		{
			OnTryWindowCloseEvent.invoke();
		}
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Window::openTween(float delayTime, float speed, TWEEN_TYPE type)
{
	if (!isTweening())
		_goalSize = _size;
	_tweenType = type;
	_delayTime = delayTime;
	_startSize = _size;
	_speed = speed;
	switch (type)
	{
	case TWEEN_TYPE::HORIZON:
	{
		_startSize.x = 0;
	}
	break;
	case TWEEN_TYPE::VERTICAL:
	{
		_startSize.y = 0;
	}
	break;
	}
	_timer = 0.f;
	_isTweenEnd = false;
}

void Window::closeTween(float delayTime, float speed, TWEEN_TYPE type)
{
	_tweenType = type;
	_delayTime = delayTime;
	_startSize = _size;
	_goalSize = _size;
	_speed = speed;
	switch (type)
	{
	case TWEEN_TYPE::HORIZON:
	{
		_goalSize.x = 0;
	}
	break;
	case TWEEN_TYPE::VERTICAL:
	{
		_goalSize.y = 0;
	}
	break;
	}
	_timer = 0.f;
	_isTweenEnd = false;
}

void Window::closeWindow()
{
	_closeable = true;
	GET_SINGLETON(Core)->OnMessageProcessEvent += [this]()
		{
			GET_SINGLETON(Core)->OnMessageProcessEvent -= [this]() {};
			SendMessage(_hWnd, WM_CLOSE, 0, 0);
		};
	_isClosed = true;
}

void Window::openWindow()
{
	OnWindowOpenEvent.invoke();
	GET_SINGLETON(Core)->OnMessageProcessEvent += [this]()
		{
			GET_SINGLETON(Core)->OnMessageProcessEvent -= [this]() {};
			WNDCLASS wc = { 0 }; // 구조체를 0으로 초기화

			wc.lpfnWndProc = Window::wndProc; // 윈도우 프로시저 함수 설정
			wc.hInstance = GET_SINGLETON(Core)->getHInstance(); // 인스턴스 핸들 설정
			wc.lpszClassName = L"엄준식"; // 클래스 이름 설정
			wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 배경색 설정

			RegisterClass(&wc);

			Vector2 fixedPos = GET_LEFTTOPPOS(_position, _size);

			_hWnd = CreateWindowEx(
				0,
				L"엄준식",
				_name.c_str(),
				WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
				fixedPos.x, fixedPos.y,
				_size.x, _size.y,
				NULL,
				NULL,
				GET_SINGLETON(Core)->getHInstance(),
				this
			);
			_leftTopPosition = fixedPos;
			ShowWindow(_hWnd, SW_SHOW);
			_hMainDC = GetDC(_hWnd);
		};
}

void Window::close()
{
	_closeable = true;
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, 0);
	GET_SINGLETON(EventManager)->deleteWindow(this);
	HWND hWnd = _hWnd;
	GET_SINGLETON(Core)->OnMessageProcessEvent += [hWnd]()
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		};
	_isDead = true;
}

void Window::moveWindow(const Vector2& pos)
{
	Vector2 leftTop = GET_LEFTTOPPOS(pos, _size);
	SetWindowPos(_hWnd, NULL, leftTop.x, leftTop.y, _size.x, _size.y, SWP_NOZORDER);
	_position = pos;
	_leftTopPosition = leftTop;
}

void Window::setWindowName(const wstring& name)
{
	SetWindowText(_hWnd, name.c_str());
}

void Window::setPriority(int priority)
{
	_priority = priority;
	GET_SINGLETON(WindowManager)->sortWindow();
}

void Window::update()
{
	if (!_isTweenEnd)
	{
		if (DELTATIME == 0)
			_timer += 0.008f * _speed;
		else
			_timer += DELTATIME * _speed;
		if (_timer < _delayTime)
			return;
		_size.x = std::lerp(_startSize.x, _goalSize.x, utils::Ease::outQuad(_timer - _delayTime));
		_size.y = std::lerp(_startSize.y, _goalSize.y, utils::Ease::outQuad(_timer - _delayTime));
		moveWindow(_position);
		if (_timer > _delayTime + 1.f)
		{
			_isTweenEnd = true;
			OnTweenEndEvent.invoke();
		}
		return;
	}
}