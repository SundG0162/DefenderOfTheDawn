#pragma once
#include "UI.h"
class Sprite;
class ImageUI : public UI
{
public:
	ImageUI(Sprite* sprite);
	~ImageUI();
public:
	void update() override;
	void render(HDC hdc) override;
public:
	void setSprite(Sprite* sprite);
};

