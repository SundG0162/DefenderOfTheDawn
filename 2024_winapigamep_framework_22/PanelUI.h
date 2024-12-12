#pragma once
#include "UI.h"
class PanelUI : public UI
{
public:
	PanelUI();
	~PanelUI();
public:
	void update() override;
	void render(HDC hdc) override;
public:
	void addUI(const wstring& key, UI* ui);
	template<typename T>
	T* getUI(const wstring& key)
	{
		T* ui = nullptr;
		auto iter = _uiMap.find(key);
		if (iter != _uiMap.end())
		{
			ui = dynamic_cast<T*>(iter->second);
		}
		if (ui)
			return ui;
		iter = _disabledUiMap.find(key);
		if (iter != _disabledUiMap.end())
		{
			ui = dynamic_cast<T*>(iter->second);
		}
		return ui;
	}
	void removeUI(const wstring& key);
	void enableUI(const wstring& key);
	void disableUI(const wstring& key);
private:
	map<wstring, UI*> _uiMap;
	map<wstring, UI*> _disabledUiMap;
};

