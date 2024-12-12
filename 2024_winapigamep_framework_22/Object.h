#pragma once
class Component;
class Object
{
public:
	Object();
	virtual ~Object();
public:
	virtual void update() abstract;
	virtual void render(HDC hdc) abstract;
	virtual void lateUpdate();
	virtual void componentUpdate();
	virtual void componentRender(HDC hdc);
public:
	template<typename T>
	T* addComponent()
	{
		T* component = new T;
		component->setOwner(this);
		_components.push_back(component);
		return component;
	}
	template<typename T>
	T* getComponent()
	{
		T* component = nullptr;
		for (Component* compo : _components)
		{
			component = dynamic_cast<T*>(compo);
			if (component)
				break;
		}
		return component;
	}
public:
	void setPosition(const Vector2& pos) { _position = pos; }
	const Vector2& getPosition() { return _position; }
	void setSize(const Vector2& size) { _size = size; }
	const Vector2& getSize() { return _size; }
	void setDead() { _isDead = true; }
	const bool& isDead() { return _isDead; }
protected:
	Vector2 _position;
	Vector2 _size;
	bool _isDead;

	vector<Component*> _components;
};