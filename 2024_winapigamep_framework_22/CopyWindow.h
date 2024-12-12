#pragma once
#include "Window.h"
class CopyWindow : public Window
{
public:
	CopyWindow(const Vector2& position, const Vector2& size, const wstring& name = L"");
	virtual ~CopyWindow();
public:
	void render(HDC hdc) override;
};