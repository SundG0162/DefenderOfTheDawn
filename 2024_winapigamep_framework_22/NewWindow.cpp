#include "pch.h"
#include "NewWindow.h"
#include "Core.h"

NewWindow::NewWindow(const Vector2& position, const Vector2& size, const wstring& name) : Window(position, size, name)
{
	_hBackDC = CreateCompatibleDC(_hMainDC);
	_hBitmap = CreateCompatibleBitmap(_hMainDC, size.x, size.y);
	SelectObject(_hBackDC, _hBitmap);
}

NewWindow::~NewWindow()
{
}

void NewWindow::render(HDC hdc)
{
	BitBlt(_hMainDC, 0, 0, _size.x, _size.y, hdc, 0, 0, SRCCOPY);
}

void NewWindow::closeWindow()
{
	DeleteObject(_hBitmap);
	DeleteDC(_hBackDC);
	ReleaseDC(_hWnd,_hMainDC);
	Window::closeWindow();
}

void NewWindow::openWindow()
{
	_isClosed = false;
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
			_hBackDC = CreateCompatibleDC(_hMainDC);
			_hBitmap = CreateCompatibleBitmap(_hMainDC, _size.x, _size.y);
			SelectObject(_hBackDC, _hBitmap);
		};
}
