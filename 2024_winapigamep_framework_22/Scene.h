#pragma once
//#include "Object.h"
class Object; // 클래스 전방선언
class Scene
{
public:
	Scene();
	virtual ~Scene(); // 가상 소멸자
public:
	virtual void init() abstract;
	virtual void update();
	virtual void lateUpdate();
	virtual void render(HDC hDC);
	virtual void release();
public:
	void addObject(Object* _obj, LAYER _type)
	{
		_objects[(UINT)_type].push_back(_obj);
	}
	void removeObject(Object* obj, LAYER layer = LAYER::END)
	{
		if (layer == LAYER::END)
		{
			for (int i = 0; i < (UINT)LAYER::END; i++)
			{
				auto iter = std::find(_objects[i].begin(), _objects[i].end(), obj);
				if (iter != _objects[i].end())
				{
					_objects[i].erase(iter);
					return;
				}
			}
		}
		else
		{
			auto iter = std::find(_objects[(UINT)layer].begin(), _objects[(UINT)layer].end(), obj);
			if (iter != _objects[(UINT)layer].end())
				_objects[(UINT)layer].erase(iter);
		}
	}
	const vector<Object*>& getLayerObjects(LAYER _type)
	{
		return _objects[(UINT)_type];
	}
protected:
	bool _setuped = false;
	vector<Object*> _objects[(UINT)LAYER::END];
};

