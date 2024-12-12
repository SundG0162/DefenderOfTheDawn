#include "pch.h"
#include "InGameScene.h"
#include "Player.h"
#include "CCTV.h"
#include "WindowUI.h"
#include "Window.h"
#include "BasicEnemy.h"
#include "SpinEnemy.h"
#include "DashEnemy.h"
#include "InvincibleEnemy.h"
#include "SpawnManager.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "EventManager.h"
#include "SpriteRenderer.h"
#include "PowerManager.h"
#include "TextUI.h"
#include "ImageUI.h"
#include "PanelUI.h"
#include "UpgradeUI.h"
#include "ResourceManager.h"
#include "PopupManager.h"
#include "Core.h"
#include "EventManager.h"
#include "PlayerManager.h"
#include "WaveManager.h"
#include "ResultManager.h"
#include "CollisionManager.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::init()
{
	_setuped = false;
	GET_SINGLETON(CollisionManager)->checkLayer(LAYER::UI, LAYER::ENEMY);
	GET_SINGLETON(CollisionManager)->checkLayer(LAYER::PLAYER, LAYER::ENEMY);
	GET_SINGLETON(PowerManager)->initialize();
	GET_SINGLETON(ResultManager)->initialize();
	GET_SINGLETON(WaveManager)->init();
	GET_SINGLETON(Core)->OnMessageProcessEvent += [this]()
		{
			if (_setuped == true)
			{
				GET_SINGLETON(Core)->OnMessageProcessEvent -= [this]() {};
				return;
			}
			_setuped = true;
			Vector2 position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
			Player* player = new Player(position, { 400,300 });
			GET_SINGLETON(SpawnManager)->setStop(false);
			setupUI();
			GET_SINGLETON(EventManager)->createObject(player, LAYER::PLAYER);
			player->OnHPChangeEvent += [this](int prev, int current)
				{
					if (current == 0)
					{
						GET_SINGLETON(EventManager)->changeScene(L"ResultScene");
					}
				};
			GET_SINGLETON(PowerManager)->modifyPower(300);
		};
}

void InGameScene::update()
{
	Scene::update();
	GET_SINGLETON(SpawnManager)->update();
	GET_SINGLETON(WaveManager)->update();
	if (GET_KEYDOWN(KEY_TYPE::ESC))
	{
		GET_SINGLETON(PowerManager)->modifyPower(500000.f);
		if (GET_SINGLETON(Core)->isPaused())
		{
			GET_SINGLETON(PopupManager)->close(L"Pause", false);
		}
		else
		{
			GET_SINGLETON(PopupManager)->popup(L"Pause", { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, true, 2.f);
		}
	}
}

void InGameScene::release()
{
	Scene::release();
	GET_SINGLETON(SpawnManager)->setStop(true);
	GET_SINGLETON(WaveManager)->release();
}

void InGameScene::setupUI()
{
#pragma region PowerPanel
	{
		PanelUI* panelUI = new PanelUI();
		Vector2 panelSize = { 200, 50 };
		Vector2 panelPosition = { SCREEN_WIDTH - panelSize.x / 2, panelSize.y / 2 + 20 };
		panelUI->setSize(panelSize);
		panelUI->setPosition({ panelSize.x / 2, panelSize.y / 2 });
		TextUI* powerText = new TextUI();
		powerText->setPosition({ panelSize.x / 2 + 16,panelSize.y / 4 });
		powerText->setupFont(25);
		powerText->setText(L"0");
		Sprite* icon = GET_SINGLETON(ResourceManager)->getSprite(L"PowerIcon");
		ImageUI* powerIcon = new ImageUI(icon);
		powerIcon->setPosition({ 32.f, panelSize.y / 2 });
		panelUI->addUI(L"PowerText", powerText);
		panelUI->addUI(L"PowerIcon", powerIcon);
		WindowUI* powerPanel = new WindowUI(panelPosition, panelSize, WINDOW_TYPE::NEW, L"Power.exe");
		powerPanel->setUI(panelUI);
		powerPanel->getWindow()->setMoveable(true);
		powerPanel->getWindow()->setCloseable(false);
		GET_SINGLETON(PowerManager)->OnPowerChangeEvent += [powerPanel](int prev, int current)
			{
				wstring value = std::format(L"{0}", current);
				powerPanel->getUI<PanelUI>()->getUI<TextUI>(L"PowerText")->setText(value);
			};
		GET_SINGLETON(EventManager)->createObject(powerPanel, LAYER::UI);
	}
#pragma endregion
#pragma region HPUI
	{
		PanelUI* panelUI = new PanelUI();
		Vector2 panelSize = { 280,90 };
		Vector2 panelPosition = { panelSize.x / 2, panelSize.y / 2 + 20 };
		panelUI->setSize(panelSize);
		panelUI->setPosition({ panelSize.x / 2, panelSize.y / 2 });
		Sprite* heart = GET_SINGLETON(ResourceManager)->getSprite(L"Heart");
		int offset = 85;
		for (int i = 0; i < 3; i++)
		{
			int x = 50 + offset * i;
			ImageUI* image = new ImageUI(heart);
			image->getComponent<SpriteRenderer>()->setScale({ 2,2 });
			image->setPosition({ x, (int)panelSize.y / 2 });
			wstring key = std::format(L"{0}", i);
			panelUI->addUI(key.c_str(), image);
		}
		WindowUI* hpUI = new WindowUI(panelPosition, panelSize, WINDOW_TYPE::NEW, L"HP.exe");
		hpUI->setUI(panelUI);
		hpUI->getWindow()->setMoveable(true);
		hpUI->getWindow()->setCloseable(false);
		Player* player = GET_SINGLETON(PlayerManager)->getPlayer();
		player->OnHPChangeEvent += [hpUI](int prev, int current)
			{
				if (prev > current)
				{
					wstring key = std::format(L"{0}", current);
					hpUI->getUI<PanelUI>()->disableUI(key.c_str());
				}
				else
				{
					wstring key = std::format(L"{0}", current - 1);
					hpUI->getUI<PanelUI>()->enableUI(key.c_str());
				}
			};
		GET_SINGLETON(EventManager)->createObject(hpUI, LAYER::UI);
	}
#pragma endregion
#pragma region ItemUI
	{
		PanelUI* panelUI = new PanelUI();
		Vector2 panelSize = { 320,110 };
		Vector2 panelPosition = { panelSize.x / 2, panelSize.y / 2 + 160 };
		panelUI->setPosition(panelPosition);
		panelUI->setSize({ panelSize.x, panelSize.y + 20 });
		wstring names[3] = { L"CameraIcon", L"TorchIcon", L"Upgrade" };
		wstring prices[3] = { L"50",L"40" ,L"70" };
		int offset = 92;
		for (int i = 0; i < 3; i++)
		{
			int x = 60 + offset * i;
			Sprite* sprite = GET_SINGLETON(ResourceManager)->getSprite(names[i].c_str());
			ImageUI* image = new ImageUI(sprite);
			TextUI* numberText = new TextUI();
			numberText->setupFont(20);
			wstring number = std::format(L"{0}", i + 1);
			numberText->setText(number);
			numberText->setPosition({ x - 20, 5 });
			image->getComponent<SpriteRenderer>()->setScale({ 2.3f,2.3f });
			image->setPosition({ x, (int)panelSize.y / 2 + 10 });
			Sprite* powerSprite = GET_SINGLETON(ResourceManager)->getSprite(L"PowerIcon");
			ImageUI* powerImage = new ImageUI(powerSprite);
			powerImage->getComponent<SpriteRenderer>()->setScale({ 0.6f,0.6f });
			powerImage->setPosition({ x - 28, (int)panelSize.y + 7 });
			TextUI* priceText = new TextUI();
			priceText->setPosition({ x, (int)panelSize.y - 3 });
			priceText->setupFont(16);
			priceText->setText(prices[i]);
			panelUI->addUI(names[i], image);
			panelUI->addUI(number, numberText);
			panelUI->addUI(number + L"Price", priceText);
			panelUI->addUI(number + L"PowerIcon", powerImage);
		}
		Sprite* select = GET_SINGLETON(ResourceManager)->getSprite(L"Selected");
		ImageUI* selectImage = new ImageUI(select);
		selectImage->getComponent<SpriteRenderer>()->setScale({ 2.3f,2.3f });
		selectImage->setPosition({ 60,(int)panelSize.y / 2 + 10 });
		panelUI->addUI(L"Select", selectImage);
		WindowUI* itemUI = new WindowUI(panelPosition, { panelSize.x, panelSize.y + 20 }, WINDOW_TYPE::NEW, L"Items.exe");
		itemUI->setUI(panelUI);
		itemUI->getWindow()->setMoveable(true);
		itemUI->getWindow()->setCloseable(false);
		Player* player = GET_SINGLETON(PlayerManager)->getPlayer();
		player->OnItemChangeEvent += [itemUI, offset, panelSize](PLAYER_ITEM item)
			{
				int x = 60 + offset * (int)item;
				itemUI->getUI<PanelUI>()->getUI<ImageUI>(L"Select")->setPosition({ x, (int)panelSize.y / 2 + 10 });
			};
		player->OnItemUseEvent += [itemUI](PLAYER_ITEM item, int value)
			{
				wstring key = std::format(L"{0}Price", (int)item + 1);
				wstring price = std::format(L"{0}", value);
				itemUI->getUI<PanelUI>()->getUI<TextUI>(key)->setText(price);
			};
		GET_SINGLETON(EventManager)->createObject(itemUI, LAYER::UI);
	}
#pragma endregion
}
