#pragma once
enum class KEY_TYPE
{
	LEFT, RIGHT, UP, DOWN,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,
	CTRL, LALT, LSHIFT, SPACE,
	ENTER, TAB, ESC, LBUTTON, RBUTTON,
	NUM_1, NUM_2, NUM_3, LAST
};
enum class KEY_STATE
{					
	NONE, DOWN, UP, PRESS, END
};
struct KeyInfo
{
	KEY_STATE state;
	bool isPrevCheck;
};

class InputManager
{
	DECLARE_SINGLETON(InputManager);
public:
	void init();
	void update();
	const KEY_STATE& getKey(KEY_TYPE _eKey) const
	{
		return _keys[(int)_eKey].state;
	}
	const POINT& getMousePos() const { return _mousePoint; }
private:
	POINT			 _mousePoint = {};
	vector<KeyInfo> _keys;
	int				 _vkKeys[(int)KEY_TYPE::LAST] =
	{ VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, 'Q','W','E','R',
	'T','Y','U','I','O','P',
	'A','S','D','F','G','H','J','K','L',
	'Z','X','C','V','B','N','M',
	VK_CONTROL, VK_LMENU, VK_LSHIFT, VK_SPACE,
		VK_RETURN, VK_TAB, VK_ESCAPE,
		VK_LBUTTON, VK_RBUTTON,'1','2','3'};
};

