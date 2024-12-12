#include "pch.h"
#include "TutorialScene.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "ImageUI.h"
#include "TextUI.h"
#include "WindowUI.h"
#include "Window.h"
#include "SpriteRenderer.h"
#include "SceneManager.h"
#include "Core.h"
#include "NewWindow.h"

TutorialScene::TutorialScene()
{
	_currentIndex = -1;
	_panelSize = { 512,512 };
	_panelPosition = { (float)SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - _panelSize.y / 6 };
	_setuped = false;
	_panelUI = nullptr;
	_textUI = nullptr;
	for (int i = 1; i <= 6; i++)
	{
		wstring name = std::format(L"TutorialPanel{0}", i);
		_panelSprites.push_back(GET_SINGLETON(ResourceManager)->getSprite(name));
	}
	_tutorialTexts.push_back(L"WASD를 통해 CCTV.exe를 움직여 근처를 탐색할 수 있습니다.\nCCTV.exe는 기본적인 공격 수단입니다.");
	_tutorialTexts.push_back(L"인게임에서 바이러스를 잡거나 발전기를 돌려 전력을 얻을 수 있습니다.\n전력을 통해 각종 기기를 업그레이드 할 수 있습니다.");
	_tutorialTexts.push_back(L"숫자 키를 눌러 아이템을 선택하고\n스페이스, 엔터키를 통해\n사용할 수 있습니다.");
	_tutorialTexts.push_back(L"CCTV.exe로 적을 비추거나 아이템을 통해 바이러스를 잡을 수 있습니다.\n아, 참고로 CCTV가 공격할때마다 전력이 소모됩니다.");
	_tutorialTexts.push_back(L"바이러스가 모니터에 3번 이상 도달할 경우 게임은 종료됩니다.");
	_tutorialTexts.push_back(L"게임 도중에 F키를 눌러 발전기 창을 열 수 있습니다.\n꾸준히 돌리는게 좋지만 잘못 열었다간 CCTV가 조작 불가능해지니 조심하세요.");
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::init()
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
			_panelUI = new WindowUI(_panelPosition, _panelSize, WINDOW_TYPE::NEW, L"TutorialPanel.exe");
			ImageUI* image = new ImageUI(nullptr);
			image->setPosition({ _panelSize.x / 2, _panelSize.y / 2 });
			image->getComponent<SpriteRenderer>()->setScale({ 3,3 });
			_panelUI->setUI(image);
			_textUI = new WindowUI({ (int)_panelPosition.x, SCREEN_HEIGHT - 150 }, { SCREEN_WIDTH,300 }, WINDOW_TYPE::NEW, L"TutorialText.exe");
			TextUI* text = new TextUI();
			text->setupFont(40);
			_textUI->setUI(text);
			text->setPosition({ SCREEN_WIDTH / 2,(int)_textUI->getSize().y / 4 });
			_textUI->getWindow()->setMoveable(false);
			_textUI->getWindow()->setCloseable(false);
			WindowUI* nextBtn = new WindowUI({ _panelPosition.x + _panelSize.x / 1.5f, _panelPosition.y - _panelSize.y / 2 - 50 }, { 300,70 }, WINDOW_TYPE::NEW, L"Next.exe");
			{
				TextUI* text = new TextUI();
				Vector2 size = nextBtn->getSize();
				text->setupFont(30);
				text->setPosition({ size.x / 2,size.y / 4 });
				text->setText(L"닫아서 다음으로");
				nextBtn->setUI(text);
			}
			nextBtn->getWindow()->setPriority(UI_PRIORITY + 2);
			nextBtn->getWindow()->OnTryWindowCloseEvent += [this]()
				{
					nextTutorial();
				};

			WindowUI* exitBtn = new WindowUI({ _panelPosition.x - _panelSize.x, _panelPosition.y - _panelSize.y / 2 - 100 }, { 300,70 }, WINDOW_TYPE::NEW, L"Exit.exe");
			{
				TextUI* text = new TextUI();
				Vector2 size = nextBtn->getSize();
				text->setupFont(30);
				text->setPosition({ size.x / 2,size.y / 4 });
				text->setText(L"닫아서 나가기");
				exitBtn->setUI(text);
			}
			exitBtn->getWindow()->setPriority(UI_PRIORITY + 2);
			exitBtn->getWindow()->OnTryWindowCloseEvent += [this]()
				{
					GET_SINGLETON(EventManager)->changeScene(L"TitleScene");
				};

			_panelUI->getWindow()->setMoveable(false);
			_panelUI->getWindow()->setCloseable(false);
			_textUI->getWindow()->setMoveable(false);
			_textUI->getWindow()->setCloseable(false);
			nextBtn->getWindow()->setMoveable(true);
			nextBtn->getWindow()->setCloseable(false);
			exitBtn->getWindow()->setMoveable(true);
			exitBtn->getWindow()->setCloseable(false);
			_currentIndex = -1;
			nextTutorial();
			GET_SINGLETON(EventManager)->createObject(_panelUI, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(_textUI, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(nextBtn, LAYER::UI);
			GET_SINGLETON(EventManager)->createObject(exitBtn, LAYER::UI);
		};
}

void TutorialScene::nextTutorial()
{
	_currentIndex++;
	if (_currentIndex == _tutorialTexts.size())
	{
		GET_SINGLETON(EventManager)->changeScene(L"TitleScene");
		return;
	}
	else if (_currentIndex > _tutorialTexts.size())
		return;
	_panelUI->getUI<ImageUI>()->setSprite(_panelSprites[_currentIndex]);
	_textUI->getUI<TextUI>()->setText(_tutorialTexts[_currentIndex]);
}