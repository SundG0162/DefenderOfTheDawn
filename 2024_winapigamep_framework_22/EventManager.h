#pragma once
class Object;
class Window;
struct Event
{
	EVENT_TYPE eventType;
	void* object;
	LAYER objectLayer;
	wstring name;
public:
	bool operator==(const Event& other)
	{
		return eventType == other.eventType && object == other.object;
	}
};
class EventManager
{
	DECLARE_SINGLETON(EventManager);
public:
	void update();
	void deadObjectClear();
	void deleteObject(Object* _pObj);
	void createObject(Object* obj, LAYER layer);
	void excludeObject(Object* obj, LAYER layer);
	void createWindow(Window* window);
	void deleteWindow(Window* window);
	void excludeWindow(Window* window);
	void changeScene(const wstring& name);
private:
	void excute(const Event& _eve);
private:
	vector<Event> _events;
	vector<void*> _deadObjects;
};