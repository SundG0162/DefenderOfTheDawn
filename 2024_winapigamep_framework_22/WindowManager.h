#pragma once
class Window;
class WindowManager
{
	DECLARE_SINGLETON(WindowManager)
	~WindowManager();
public:
	void update();
	void render();
	void release();
public:
	void sortWindow();
	static bool compareWindow(Window* w1, Window* w2);
	void addWindow(Window* window) 
	{
		_windows.push_back(window); 
		sortWindow();
	}
	void removeWindow(Window* window)
	{
		auto iter = std::find(_windows.begin(), _windows.end(), window);
		if (iter != _windows.end())
		{
			_windows.erase(iter);
		}
		sortWindow();
	}
private:
	int _frameCounter = 0;
	vector<Window*> _windows;
};

