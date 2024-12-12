#pragma once
#include "UI.h"
class Player;
class Upgrade;
class TextUI;
class ImageUI;
class UpgradeUI : public UI
{
public:
	UpgradeUI();
	~UpgradeUI();
public:
	void update() override;
	void render(HDC hdc) override;
public:
	void setUpgrade(Upgrade* upgrade);
private:
	Player* _player;
	TextUI* _titleText;
	TextUI* _descriptionText;
	ImageUI* _iconImage;
};