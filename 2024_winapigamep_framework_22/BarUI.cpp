#include "pch.h"
#include "BarUI.h"
#include "GDISelector.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "Window.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Sprite.h"

BarUI::BarUI(const Vector2& position, const Vector2& size) : UI()
{
	_position = position;
	_size = size;
	_fillAmount = 1;
	_isVertical = false;
	_isReverse = false;
	SpriteRenderer* renderer = addComponent<SpriteRenderer>();
	Sprite* sprite = GET_SINGLETON(ResourceManager)->getSprite(L"BarUI");
	renderer->setSprite(sprite);
	renderer->setScale({ size.x / 32, size.y / 4 });
}

BarUI::~BarUI()
{
}

void BarUI::update()
{
	_fillAmount -= DELTATIME * 0.2f;
}

void BarUI::render(HDC hdc)
{
	float fillAmount = 1 - _fillAmount / 1.f; // 1-0을 0-1로조정
	utils::Drawer::renderRectColor(hdc, _position, _size.x, _size.y, RGB(255, 255, 255), RGB(255, 255, 255));
	Vector fillPos = _position;
	float multiplier = _isReverse ? -1 : 1;
	fillPos.x = _position.x + (_size.x * (1.0f - fillAmount) / 2.0f) * multiplier;
	utils::Drawer::renderRectColor(hdc, fillPos, _size.x * fillAmount, _size.y, RGB(0, 0, 0), RGB(0, 0, 0));
	componentRender(hdc);
}
