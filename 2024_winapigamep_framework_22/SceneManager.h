#pragma once
#include "Scene.h"
class Object;
class SceneManager
{
	DECLARE_SINGLETON(SceneManager);
public:
	void init();
	void update();
	void render(HDC hDC);
public:
	void registerScene(const wstring& _sceneName, 
					std::shared_ptr<Scene> _scene);
	void loadScene(const wstring& _sceneName);
	template<typename T>
	T* createObject(LAYER layer)
	{
		T* obj = new T;
		_currentScene->addObject(obj, layer);
		return obj;
	}
public:
	const std::shared_ptr<Scene>& getCurrentScene() const
	{
		return _currentScene;
	}
private:
	map<wstring, std::shared_ptr<Scene>> _sceneMap;
	std::shared_ptr<Scene> _currentScene;
};

