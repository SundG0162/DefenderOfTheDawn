#pragma once
#include <thread>
class BaseWindow
{
public:
	BaseWindow();
	~BaseWindow();
public:
	int run(HINSTANCE hInst, LPWSTR _lpCmdline, int nCmdShow);
public:
	static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	ATOM myRegisterClass(); // 1
	void createWindow();   // 2
	void showWindow(int nCmdShow); // 3
	void updateWindow(); // 4
	int  messageLoop(); // 5
private:
	std::thread _mainLoopThread;
	HINSTANCE _hInstance;
	HWND	  _hWnd;
};

 