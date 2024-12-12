#include "pch.h"
#include "WindowManager.h"
#include "Core.h"
#include "Window.h"
#include "CopyWindow.h"
#include "NewWindow.h"

WindowManager::~WindowManager()
{
}

void WindowManager::update()
{
	for (Window* window : _windows)
	{
		if (window == nullptr || window->isDead())
		{
			auto iter = std::find(_windows.begin(), _windows.end(), window);
			if (iter != _windows.end())
				_windows.erase(iter);
			continue;
		}
		window->update();
	}

	if (_windows.size() <= 0) return;
	HDWP hDwp = BeginDeferWindowPos(_windows.size());
	HWND bottom = _windows[0]->getHWnd();
	for (Window* window : _windows)
	{
		hDwp = DeferWindowPos(hDwp,
			window->getHWnd(),
			bottom,
			0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
		bottom = window->getHWnd();
	}
	EndDeferWindowPos(hDwp);
}

void WindowManager::render()
{
	for (Window* window : _windows)
	{
		if (window == nullptr) continue;
		if (window->isDead()) continue;
		CopyWindow* copyWindow = dynamic_cast<CopyWindow*>(window);
		if (copyWindow)
		{
			copyWindow->render(GET_SINGLETON(Core)->getBackDC());
			continue;
		}
		NewWindow* newWindow = dynamic_cast<NewWindow*>(window);
		if (newWindow)
		{
			newWindow->render(newWindow->getBackDC());
			continue;
		}
	}
}

void WindowManager::release()
{
	for (Window* window : _windows)
	{
		if (window == nullptr || !window->isDead()) continue;
		window->close();
		delete window;
		window = nullptr;
	}
	_windows.clear();
}

void WindowManager::sortWindow()
{
	std::sort(_windows.begin(), _windows.end(), WindowManager::compareWindow);
}

bool WindowManager::compareWindow(Window* w1, Window* w2)
{
	return w1->getPriority() > w2->getPriority();
}
