#include "pch.h"
#include "InputManager.h"
#include "Core.h"
void InputManager::init()
{
	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
		_keys.push_back(KeyInfo{KEY_STATE::NONE, false});
}

void InputManager::update()
{
	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
	{
		if (GetAsyncKeyState(_vkKeys[i]))
		{
			if (_keys[i].isPrevCheck)
				_keys[i].state = KEY_STATE::PRESS;
			else
				_keys[i].state = KEY_STATE::DOWN;
			_keys[i].isPrevCheck = true;
		}
		else
		{
			if (_keys[i].isPrevCheck)
				_keys[i].state = KEY_STATE::UP;
			else
				_keys[i].state = KEY_STATE::NONE;
			_keys[i].isPrevCheck = false;
		}
	}
	::GetCursorPos(&_mousePoint);
	::ScreenToClient(NULL, &_mousePoint);
}
