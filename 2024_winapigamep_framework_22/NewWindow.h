#pragma once
#include "Window.h"
class NewWindow : public Window
{
public:
	NewWindow(const Vector2& position, const Vector2& size, const wstring& name = L"");
	virtual ~NewWindow();
public:
	void render(HDC hdc) override;
public:
	void closeWindow() override;
	void openWindow() override;
public:
	const HDC& getBackDC() { return _hBackDC; }
private:
	HDC _hBackDC;
	HBITMAP _hBitmap;
};

