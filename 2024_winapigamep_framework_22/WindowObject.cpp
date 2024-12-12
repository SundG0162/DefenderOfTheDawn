#include "pch.h"
#include "WindowObject.h"
#include "Window.h"
#include "NewWindow.h"
#include "CopyWindow.h"
#include "TimeManager.h"
#include "EventManager.h"

WindowObject::WindowObject(const Vector2& position, const Vector2& size, const WINDOW_TYPE& type, const wstring& name)
{
	if (type == WINDOW_TYPE::COPY)
		_position = position;
	_size = size;
	if (type == WINDOW_TYPE::NEW)
		_position = _size / 2;
	_type = type;
	switch (type)
	{
	case WINDOW_TYPE::NEW:
	{
		_window = new NewWindow(position, size, name);
	}
	break;
	case WINDOW_TYPE::COPY:
	{
		_window = new CopyWindow(position, size, name);
	}
	break;
	}
	_window->OnWindowCloseEvent += [this]()
		{
			GET_SINGLETON(EventManager)->deleteObject(this);
		};
}

WindowObject::~WindowObject()
{
	_window->close();
}

void WindowObject::openTween(float delayTime)
{
	_window->openTween(delayTime);
}