#include "pch.h"
#include "EventManager.h"
#include "Core.h"
#include "SceneManager.h"
#include "WindowManager.h"
#include "Object.h"
#include "Window.h"
void EventManager::update()
{
	deadObjectClear();

	for (auto& eve : _events)
		excute(eve);
	_events.clear();
}

void EventManager::deadObjectClear()
{
	for (int i = 0; i < _deadObjects.size(); i++)
	{
		void* obj = _deadObjects[i];
		if (obj != nullptr)
		{
			{
				Window* ptr = static_cast<Window*>(obj);
				if (ptr != nullptr)
				{
					delete ptr;
					_deadObjects[i] = nullptr;
					continue;
				}
			}
			{
				Object* ptr = static_cast<Object*>(obj);
				if (ptr != nullptr)
				{
					delete ptr;
					_deadObjects[i] = nullptr;
				}
			}
		}
	}
	_deadObjects.clear();
}

void EventManager::deleteObject(Object* _pObj)
{
	Event eve = {};
	eve.eventType = EVENT_TYPE::DELETE_OBJECT;
	eve.object = _pObj;

	if (std::find(_events.begin(), _events.end(), eve) == _events.end())
	{
		_events.push_back(eve);
	}
}

void EventManager::createObject(Object* obj, LAYER layer)
{
	Event eve = {};
	eve.eventType = EVENT_TYPE::CREATE_OBJECT;
	eve.object = obj;
	eve.objectLayer = layer;

	if (std::find(_events.begin(), _events.end(), eve) == _events.end())
	{
		_events.push_back(eve);
	}
}

void EventManager::excludeObject(Object* obj, LAYER layer)
{
	Event eve = {};
	eve.eventType = EVENT_TYPE::EXCLUDE_OBJECT;
	eve.object = obj;
	eve.objectLayer = layer;

	if (std::find(_events.begin(), _events.end(), eve) == _events.end())
	{
		_events.push_back(eve);
	}
}

void EventManager::createWindow(Window* window)
{
	Event eve = {};
	eve.eventType = EVENT_TYPE::CREATE_WINDOW;
	eve.object = window;

	if (std::find(_events.begin(), _events.end(), eve) == _events.end())
	{
		_events.push_back(eve);
	}
}

void EventManager::deleteWindow(Window* window)
{
	Event eve = {};
	eve.eventType = EVENT_TYPE::DELETE_WINDOW;
	eve.object = window;

	if (std::find(_events.begin(), _events.end(), eve) == _events.end())
	{
		_events.push_back(eve);
	}
}

void EventManager::excludeWindow(Window* window)
{
	Event eve = {};
	eve.eventType = EVENT_TYPE::EXCLUDE_WINDOW;
	eve.object = window;

	if (std::find(_events.begin(), _events.end(), eve) == _events.end())
	{
		_events.push_back(eve);
	}
}

void EventManager::changeScene(const wstring& name)
{
	Event eve = {};
	eve.eventType = EVENT_TYPE::SCENE_CHANGE;
	eve.name = name;
	if (std::find(_events.begin(), _events.end(), eve) == _events.end())
	{
		_events.push_back(eve);
	}
}

void EventManager::excute(const Event& _eve)
{
	switch (_eve.eventType)
	{
	case EVENT_TYPE::DELETE_OBJECT:
	{
		Object* pDeadObj = (Object*)_eve.object;
		pDeadObj->setDead();
		_deadObjects.push_back(pDeadObj);
	}
	break;
	case EVENT_TYPE::DELETE_WINDOW:
	{
		Window* pDeadObj = (Window*)_eve.object;
		pDeadObj->setDead();
		_deadObjects.push_back(pDeadObj);
	}
	break;
	case EVENT_TYPE::CREATE_WINDOW:
	{
		GET_SINGLETON(WindowManager)->addWindow((Window*)_eve.object);
	}
	break;
	case EVENT_TYPE::EXCLUDE_WINDOW:
	{
		GET_SINGLETON(WindowManager)->removeWindow((Window*)_eve.object);
	}
	break;
	case EVENT_TYPE::CREATE_OBJECT:
	{
		GET_SINGLETON(SceneManager)->getCurrentScene()->addObject((Object*)_eve.object, _eve.objectLayer);
	}
	break;
	case EVENT_TYPE::EXCLUDE_OBJECT:
	{
		GET_SINGLETON(SceneManager)->getCurrentScene()->removeObject((Object*)_eve.object, _eve.objectLayer);
	}
	break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		wstring name = _eve.name;
		GET_SINGLETON(SceneManager)->loadScene(name);
	}
	break;
	}
}
