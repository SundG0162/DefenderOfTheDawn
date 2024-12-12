#include "pch.h"
#include "BaseWindow.h"
#include "Resource.h"
#include "Core.h"
#include <functional>
BaseWindow::BaseWindow()
	: _hWnd(nullptr)
	, _hInstance(nullptr)
{
}

BaseWindow::~BaseWindow()
{
}

int BaseWindow::run(HINSTANCE hInst, LPWSTR lpCmdline, int nCmdShow)
{
	this->_hInstance = hInst;
	this->myRegisterClass();
	this->createWindow();
	this->showWindow(nCmdShow);
	this->updateWindow();
	if (!GET_SINGLETON(Core)->init(_hWnd, _hInstance))
		MessageBox(_hWnd, L"Core init Error", L"Error", MB_OK);
	return messageLoop();
}

LRESULT BaseWindow::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

ATOM BaseWindow::myRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BaseWindow::wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _hInstance;
	wcex.hIcon = LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_ICON2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"2-2 Gamep";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

	return RegisterClassExW(&wcex);
}

void BaseWindow::createWindow()
{
	int ResolutionX = GetSystemMetrics(SM_CXSCREEN);
	int ResolutionY = GetSystemMetrics(SM_CYSCREEN);


	_hWnd = CreateWindowW(
		L"2-2 Gamep", // 윈도우 클래스 식별자
		L"준용의 윈도우",   // 제목
		WS_POPUP, // 윈도우 어떤 스타일로 만들것인가
		0,  // ★ 띄울 위치의 LEFT
		0,             // ★ 띄울 위치의 TOP
		SCREEN_WIDTH,             // ★ 해상도X
		SCREEN_HEIGHT,             // ★ 해상도Y
		nullptr,       // 부모 윈도우 어쩌구라서 무시
		nullptr,       // 메뉴쓸꺼냐
		_hInstance,     // 내 프로그램 인스턴스 값 
		nullptr);      // 자식 윈도우 관련된것 무시
}

void BaseWindow::showWindow(int nCmdShow)
{
	// global namespace
	ShowWindow(_hWnd, SW_MINIMIZE);
}

void BaseWindow::updateWindow()
{
	::UpdateWindow(_hWnd); // WM_PAINT
}

int BaseWindow::messageLoop()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg)); // 0 초기화
	_mainLoopThread = std::thread(std::bind(&Core::gameLoop, GET_SINGLETON(Core)));
	while (true)
	{
		GET_SINGLETON(Core)->onMessageProcess();
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	GET_SINGLETON(Core)->endGame();
	GET_SINGLETON(Core)->cleanUp();
	_mainLoopThread.join();
	return (int)msg.wParam;
}
