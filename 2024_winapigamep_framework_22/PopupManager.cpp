#include "pch.h"
#include "PopupManager.h"
#include "Core.h"
#include "WindowUI.h"
#include "UI.h"
#include "EventManager.h"
#include "Window.h"
#include "WindowUI.h"
#include "PlayerManager.h"
#include "Player.h"
#include "PowerGenerator.h"
#include "TimeManager.h"
#include "PanelUI.h"
#include "WindowManager.h"
#include "ResourceManager.h"
#include "TextUI.h"
#include "ImageUI.h"

PopupManager::~PopupManager()
{
	release();
}

void PopupManager::initialize()
{
#pragma region NotEnoughPower
	{
		WindowUI* ui = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, { 330,70 }, WINDOW_TYPE::NEW, L"Error.exe");
		TextUI* text = new TextUI();
		text->setupFont(34);
		text->setText(L"전력이 부족합니다.");
		text->setPosition({ 165, 18 });
		ui->setUI(text);
		ui->getWindow()->OnWindowOpenEvent += [ui]()
			{
				GET_SINGLETON(ResourceManager)->play(L"Error");
			};
		ui->getWindow()->OnTryWindowCloseEvent += [ui]()
			{
				GET_SINGLETON(PopupManager)->close(L"NotEnoughPower", false);
			};
		addPopup(L"NotEnoughPower", ui);
		ui->getWindow()->closeWindow();
		GET_SINGLETON(EventManager)->excludeWindow(ui->getWindow());
		ui->getWindow()->OnWindowCloseEvent -= [ui]() {};
	}
#pragma endregion
#pragma region Pause
	{
		Vector2 panelPosition = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		Vector2 panelSize = { 500,500 };
		WindowUI* ui = new WindowUI(panelPosition, panelSize, WINDOW_TYPE::NEW, L"Pause.exe");
		PanelUI* panel = new PanelUI();
		panel->setPosition(panelPosition);
		panel->setSize(panelSize);
		{
			TextUI* text = new TextUI();
			text->setupFont(70);
			text->setText(L"일시정지.");
			text->setPosition({ panelSize.x / 2, panelSize.y / 2 - 200 });
			panel->addUI(L"TitleText", text);
		}
		{
			TextUI* text = new TextUI();
			text->setupFont(40);
			text->setText(L"ESC를 눌러 계속하기\n닫아서 타이틀로");
			text->setPosition({ panelSize.x / 2, panelSize.y / 2 - 30 });
			panel->addUI(L"InfoText", text);
		}
		ui->setUI(panel);
		ui->getWindow()->OnWindowOpenEvent += [ui, panelPosition]()
			{
				GET_SINGLETON(Core)->setPause(true);
			};
		ui->getWindow()->OnTryWindowCloseEvent += [ui]()
			{
				GET_SINGLETON(Core)->setPause(false);
				GET_SINGLETON(PopupManager)->close(L"Pause", false);
				GET_SINGLETON(EventManager)->changeScene(L"TitleScene");
			};
		addPopup(L"Pause", ui);
		ui->getWindow()->closeWindow();
		GET_SINGLETON(EventManager)->excludeWindow(ui->getWindow());
		ui->getWindow()->OnWindowCloseEvent -= [ui]() {};
	}
#pragma endregion
#pragma region PowerGenerator
	{
		PowerGenerator* ui = new PowerGenerator({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, { 400,400 });
		ui->getWindow()->OnWindowOpenEvent += [ui]()
			{
				GET_SINGLETON(PlayerManager)->getPlayer()->setCCTVLocked(true);
			};
		ui->getWindow()->OnTryWindowCloseEvent += [ui]()
			{
				GET_SINGLETON(PlayerManager)->getPlayer()->setCCTVLocked(false);
				GET_SINGLETON(PopupManager)->close(L"PowerGenerator", false);
			};
		addPopup(L"PowerGenerator", ui);
		ui->getWindow()->closeWindow();
		GET_SINGLETON(EventManager)->excludeWindow(ui->getWindow());
		ui->getWindow()->OnWindowCloseEvent -= [ui]() {};
	}
#pragma endregion

	for (auto& pair : _uiMap)
	{
		pair.second->getWindow()->setPriority(UI_PRIORITY + 10);
	}
}

void PopupManager::release()
{
	map<wstring, WindowUI*>::iterator iter;
	for (iter = _uiMap.begin(); iter != _uiMap.end(); ++iter)
	{
		delete iter->second;
	}
	_uiMap.clear();
}

void PopupManager::addPopup(const wstring& key, WindowUI* ui)
{
	auto iter = _uiMap.find(key);
	if (iter != _uiMap.end())
		return;
	_uiMap.insert({ key, ui });
}

WindowUI* PopupManager::getPopup(const wstring& key)
{
	auto iter = _uiMap.find(key);
	if (iter != _uiMap.end())
		return iter->second;
	return nullptr;
}

void PopupManager::popup(const wstring& key, const Vector2& position, bool withTween, float speed)
{
	WindowUI* wndUI = getPopup(key);
	if (wndUI == nullptr) return;
	if (!wndUI->getWindow()->isClosed())
	{
		wndUI->getWindow()->openTween(0.f, 3.f);
		return;
	}
	wndUI->getWindow()->openWindow();
	wndUI->setPosition(position);
	wndUI->getWindow()->setCloseable(false);
	wndUI->getWindow()->setMoveable(true);
	GET_SINGLETON(EventManager)->createObject(wndUI, LAYER::UI);
	GET_SINGLETON(EventManager)->createWindow(wndUI->getWindow());
	if (withTween)
		wndUI->getWindow()->openTween(0.f, speed);
}

void PopupManager::close(const wstring& key, bool withTween, float speed)
{
	WindowUI* wndUI = getPopup(key);
	if (key == L"Pause")
	{
		GET_SINGLETON(Core)->setPause(false);
	}
	if (withTween)
	{
		wndUI->getWindow()->closeTween(0.f, speed);
		wndUI->getWindow()->OnTweenEndEvent += [this, wndUI]()
			{
				GET_SINGLETON(EventManager)->excludeWindow(wndUI->getWindow());
				GET_SINGLETON(EventManager)->excludeObject(wndUI, LAYER::UI);
				wndUI->getWindow()->closeWindow();
			};
	}
	else
	{
		GET_SINGLETON(EventManager)->excludeWindow(wndUI->getWindow());
		GET_SINGLETON(EventManager)->excludeObject(wndUI, LAYER::UI);
		wndUI->getWindow()->closeWindow();
	}
}
