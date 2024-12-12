#pragma once
#include "UI.h"
class TextUI : public UI
{
public:
	TextUI();
	~TextUI();
public:
	void setupFont(float fontSize, const wstring& fontName = L"Galmuri9 Regular", float fontWeight = 400);
	void setColor(const COLORREF& color) { _color = color; }
	void setText(const wstring& text) { _text = text; }
	Vector2 getTextSize();
public:
	void update() override;
	void render(HDC hdc) override;
private:
	wstring _text;
	COLORREF _color;
	HFONT _hFont;
	SIZE _size;
};