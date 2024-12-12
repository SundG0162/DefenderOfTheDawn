#include "pch.h"
#include "Core.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "WindowManager.h"
#include "EventManager.h"
#include "WaveManager.h"
#include "SpawnManager.h"
#include "PopupManager.h"

bool Core::init(HWND _hwnd, HINSTANCE hInstance)
{
	// 변수 초기화
	_hWnd = _hwnd;
	_hInstance = hInstance;
	_hDC = ::GetDC(_hWnd);
	_hBackDC = 0;
	_hBitmap = 0;

	// 더블 버퍼링
	// 1. 생성(세팅)
	_hBitmap = ::CreateCompatibleBitmap(_hDC, SCREEN_WIDTH, SCREEN_HEIGHT);
	_hBackDC = ::CreateCompatibleDC(_hDC);

	// 2. 연결
	::SelectObject(_hBackDC, _hBitmap);

	createGDI();
	// === Manager init === 
	GET_SINGLETON(TimeManager)->init();
	GET_SINGLETON(InputManager)->init();
	GET_SINGLETON(ResourceManager)->init();
	GET_SINGLETON(SceneManager)->init();
	GET_SINGLETON(PopupManager)->initialize();
	GET_SINGLETON(EventManager)->update();
	AddFontResource(L"Galmuri9 Regular.ttf");
	return true;
}
void Core::cleanUp()
{
	GET_SINGLETON(SceneManager)->getCurrentScene()->release();
	GET_SINGLETON(PopupManager)->release();
	GET_SINGLETON(ResourceManager)->release();
	::DeleteDC(_hBackDC);	//createdc한거
	::DeleteObject(_hBitmap); // createbitmap 한거
	::ReleaseDC(_hWnd, _hDC);
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(_colorPens[i]);
	}
	for (int i = 1; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		// Hollow 제외하고
		DeleteObject(_colorBrushes[i]);
	}
}

void Core::gameLoop()
{
	while (!_isGameEnd)
	{
		cout << "update 시작";
		mainupdate();
		cout << "update 끝";
		cout << "render 시작"; 
		mainrender();
		cout << "render 끝";
		cout << "event 시작"; 
		GET_SINGLETON(EventManager)->update();
		cout << "event 끝";
	}
}



void Core::mainupdate()
{
	// === Manager update === 
	GET_SINGLETON(TimeManager)->update();
	GET_SINGLETON(InputManager)->update();
	GET_SINGLETON(CollisionManager)->update();
	GET_SINGLETON(SceneManager)->update();
}

void Core::mainrender()
{
	GET_SINGLETON(WindowManager)->update();
	::PatBlt(_hBackDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACKNESS);
	GET_SINGLETON(SceneManager)->render(_hBackDC);
	GET_SINGLETON(WindowManager)->render();
}
void Core::createGDI()
{
	// HOLLOW
	_colorBrushes[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	_colorBrushes[(UINT)BRUSH_TYPE::RED] = (HBRUSH)CreateSolidBrush(RGB(255, 167, 167));
	_colorBrushes[(UINT)BRUSH_TYPE::GREEN] = (HBRUSH)CreateSolidBrush(RGB(134, 229, 134));
	_colorBrushes[(UINT)BRUSH_TYPE::BLUE] = (HBRUSH)CreateSolidBrush(RGB(103, 153, 255));
	_colorBrushes[(UINT)BRUSH_TYPE::YELLOW] = (HBRUSH)CreateSolidBrush(RGB(255, 187, 0));
	_colorBrushes[(UINT)BRUSH_TYPE::WHITE] = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
	_colorBrushes[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));

	//RED GREEN BLUE PEN
	_colorPens[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	_colorPens[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	_colorPens[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	_colorPens[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	_colorPens[(UINT)PEN_TYPE::HOLLOW] = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
}

void Core::setPause(bool pause)
{
	float timeScale = pause ? 0.f : 1.f;
	GET_SINGLETON(TimeManager)->setTimeScale(timeScale);
	_isPaused = pause;
}

void Core::onMessageProcess()
{
	OnMessageProcessEvent.invoke();
}
