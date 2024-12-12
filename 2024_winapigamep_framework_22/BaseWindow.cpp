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
		L"2-2 Gamep", // ������ Ŭ���� �ĺ���
		L"�ؿ��� ������",   // ����
		WS_POPUP, // ������ � ��Ÿ�Ϸ� ������ΰ�
		0,  // �� ��� ��ġ�� LEFT
		0,             // �� ��� ��ġ�� TOP
		SCREEN_WIDTH,             // �� �ػ�X
		SCREEN_HEIGHT,             // �� �ػ�Y
		nullptr,       // �θ� ������ ��¼���� ����
		nullptr,       // �޴�������
		_hInstance,     // �� ���α׷� �ν��Ͻ� �� 
		nullptr);      // �ڽ� ������ ���õȰ� ����
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
	memset(&msg, 0, sizeof(msg)); // 0 �ʱ�ȭ
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