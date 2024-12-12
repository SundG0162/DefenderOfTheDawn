#include "pch.h"
#include "TimeManager.h"
#include "Core.h"
#include "InputManager.h"
void TimeManager::init()
{
	::QueryPerformanceCounter(&_prevCount);
	::QueryPerformanceFrequency(&_frequency);
}

void TimeManager::update()
{
	::QueryPerformanceCounter(&_currentCount);
	_deltaTime = (float)(_currentCount.QuadPart - _prevCount.QuadPart)
		/ (float)_frequency.QuadPart;
	_deltaTime *= _timeScale;
	_prevCount = _currentCount;
	_frameCount++;
	_frameTime += _deltaTime; 
	if (_frameTime >= 1.f) 
	{
		_fps = (UINT)(_frameCount / _frameTime);
		_frameTime = 0.f;
		_frameCount = 0;
		POINT mousepos = GET_MOUSEPOS;
		static wchar_t buf[100] = {};
		swprintf_s(buf, L"FPS: %d, DT: %f, Mouse: (%d, %d)",_fps, _deltaTime
										,mousepos.x, mousepos.y);
		::SetWindowText(GET_SINGLETON(Core)->getHWnd()
						, buf);
	}
}
