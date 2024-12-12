#pragma once
class UI;
class WindowUI;
class PopupManager
{
	DECLARE_SINGLETON(PopupManager)
	~PopupManager();
public:
	void initialize();
	void release();
	void addPopup(const wstring& key, WindowUI* ui);
	WindowUI* getPopup(const wstring& key);
	void popup(const wstring& key, const Vector2& position, bool withTween, float speed = 1);
	void close(const wstring& key, bool withTween, float speed = 1);
private:
	map<wstring, WindowUI*> _uiMap;
};