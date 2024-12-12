#include "pch.h"
#include "PowerGenerator.h"
#include "PanelUI.h"
#include "ImageUI.h"
#include "TextUI.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "WaveManager.h"
#include "Window.h"
#include "PowerManager.h"

PowerGenerator::PowerGenerator(const Vector2& position, const Vector2& size) : WindowUI(position, size, WINDOW_TYPE::NEW, L"PowerGenerator.exe")
{
	PanelUI* panelUI = new PanelUI();
	panelUI->setPosition(position);
	panelUI->setSize(size);
	_currentIndex = 0;
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { -1,0,1,0 };
	_keys[0] = L"W";
	_keys[1] = L"D";
	_keys[2] = L"S";
	_keys[3] = L"A";
	Vector2 pos = _size / 2;
	for (int i = 0; i < 4; i++)
	{
		Sprite* sprite = GET_SINGLETON(ResourceManager)->getSprite(_keys[i]);
		ImageUI* image = new ImageUI(sprite);
		Sprite* rSprite = GET_SINGLETON(ResourceManager)->getSprite(L"r" + _keys[i]);
		ImageUI* rImage = new ImageUI(rSprite);
		image->setPosition(pos + Vector2(dx[i] * 80, dy[i] * 80));
		image->getComponent<SpriteRenderer>()->setScale({ 3,3 });
		rImage->setPosition(pos + Vector2(dx[i] * 80, dy[i] * 80));
		rImage->getComponent<SpriteRenderer>()->setScale({ 3,3 });
		panelUI->addUI(_keys[i], image);
		panelUI->addUI(L"r" + _keys[i], rImage);
		panelUI->disableUI(L"r" + _keys[i]);
	}
	Sprite* rotateSprite = GET_SINGLETON(ResourceManager)->getSprite(L"Rotate");
	ImageUI* image = new ImageUI(rotateSprite);
	image->setPosition(pos);
	image->getComponent<SpriteRenderer>()->setScale({ 3,3 });
	panelUI->addUI(L"Rotate", image);
	setUI(panelUI);
}

PowerGenerator::~PowerGenerator()
{
}

void PowerGenerator::update()
{
	int input = -1;
	if (GET_KEYDOWN(KEY_TYPE::W))
		input = 0;
	if (GET_KEYDOWN(KEY_TYPE::D))
		input = 1;
	if (GET_KEYDOWN(KEY_TYPE::S))
		input = 2;
	if (GET_KEYDOWN(KEY_TYPE::A))
		input = 3;
	if (input == _currentIndex)
	{
		PanelUI* panel = getUI<PanelUI>();
		panel->disableUI(L"r" + _keys[_currentIndex]);
		_currentIndex++;
		GET_SINGLETON(PowerManager)->modifyPower(GET_SINGLETON(WaveManager)->getWave()/10+1);
		GET_SINGLETON(ResourceManager)->play(L"Spin");
		if (_currentIndex >= 4)
		{
			_currentIndex = 0;
		}
		panel->enableUI(L"r" + _keys[_currentIndex]);
	}
}