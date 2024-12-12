#pragma once
#include "WindowObject.h"
class UI;
class WindowUI : public WindowObject
{
public:
	WindowUI(const Vector2& position, const Vector2& size, WINDOW_TYPE type, const wstring& name);
	virtual ~WindowUI();
public:
	virtual void update() override;
	virtual void render(HDC hdc) override;
public:
	template<typename T>
	T* getUI() { return dynamic_cast<T*>(_ui); }
	void setUI(UI* ui) { _ui = ui; }
protected :
	UI* _ui;
};

