#include "pch.h"
#include "ResultScene.h"
#include "WindowUI.h"
#include "PanelUI.h"
#include "Core.h"
#include "TextUI.h"
#include "EventManager.h"
#include "ResultManager.h"
#include "Window.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::init()
{
	_setuped = false;
	GET_SINGLETON(Core)->OnMessageProcessEvent += [this]()
		{
			if (_setuped == true)
			{
				GET_SINGLETON(Core)->OnMessageProcessEvent -= [this]() {};
				return;
			}
			_setuped = true;
			Vector2 position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
			Vector2 size = { 800, 800 };
			WindowUI* ui = new WindowUI(position, size, WINDOW_TYPE::NEW, L"Result.exe");
			int power = GET_SINGLETON(ResultManager)->getTotalPower();
			int damage = GET_SINGLETON(ResultManager)->getTotalDamage();
			int enemy = GET_SINGLETON(ResultManager)->getTotalCaughtEnemy();
			wstring text = std::format(L"당신은 총 {0}의 전력을 모았고\n{1}의 데미지를 주었으며\n{2}개의 바이러스를 퇴치했습니다.", power, damage, enemy);
			TextUI* textUI = new TextUI();
			textUI->setupFont(50);
			textUI->setText(text);
			textUI->setPosition({ size.x / 2, size.y / 2 - 250 });
			TextUI* text2 = new TextUI();
			text2->setupFont(40);
			text2->setText(L"당신의 노력에 경의를 표합니다.\n\n창을 닫아서 타이틀로..");
			text2->setPosition({ size.x / 2, size.y / 2 + 20 });
			PanelUI* panel = new PanelUI();
			panel->setPosition(position);
			panel->setPosition(size);
			panel->addUI(L"ResultText", textUI);
			panel->addUI(L"Announcement", text2);
			ui->setUI(panel);
			ui->getWindow()->setMoveable(true);
			ui->getWindow()->setCloseable(false);
			ui->getWindow()->OnTryWindowCloseEvent += [this]() 
				{
					GET_SINGLETON(EventManager)->changeScene(L"TitleScene");
				};
			GET_SINGLETON(EventManager)->createObject(ui, LAYER::UI);
		};
}