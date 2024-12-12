#include "pch.h"
#include "UpgradeUI.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "PlayerManager.h"
#include "TextUI.h"
#include "ImageUI.h"
#include "Upgrade.h"

UpgradeUI::UpgradeUI()
{
	_player = GET_SINGLETON(PlayerManager)->getPlayer();
	_size = { 240, 360 };
	_position = { _size.x / 2, _size.y / 2 };
	Sprite* sprite = GET_SINGLETON(ResourceManager)->getSprite(L"UpgradeCard");
	SpriteRenderer* renderer = addComponent<SpriteRenderer>();
	renderer->setSprite(sprite);
	renderer->setScale({ _size.x / 32, _size.y / 48 });
	_titleText = new TextUI();
	_titleText->setupFont(22);
	_titleText->setText(L"Im타이틀");
	_titleText->setPosition({ _position.x, _position.y - 170 });
	_descriptionText = new TextUI();
	_descriptionText->setupFont(17);
	_descriptionText->setText(L"나는 설명이에요.\n엄준식");
	_descriptionText->setPosition(_position);
	_iconImage = new ImageUI(nullptr);
	_iconImage->getComponent<SpriteRenderer>()->setScale({ 3,3 });
	_iconImage->setPosition({ _position.x,_position.y - 70 });
}

UpgradeUI::~UpgradeUI()
{
	delete _titleText;
	delete _descriptionText;
	delete _iconImage;
}

void UpgradeUI::setUpgrade(Upgrade* upgrade)
{
	_titleText->setText(upgrade->getTitle());
	_descriptionText->setText(upgrade->getDescription());
	_iconImage->setSprite(upgrade->getIcon());
}

void UpgradeUI::update()
{

}

void UpgradeUI::render(HDC hdc)
{
	componentRender(hdc);
	_titleText->render(hdc);
	_descriptionText->render(hdc);
	_iconImage->render(hdc);
}
