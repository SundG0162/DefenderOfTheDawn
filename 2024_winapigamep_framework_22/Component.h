#pragma once
class Object;
class Component
{
public:
	Component();
	virtual ~Component();
public:
	virtual void lateUpdate() abstract;
	virtual void render(HDC hDC) abstract;
public:
	void setOwner(Object* owner) { _owner = owner; }
	Object* getOwner() const { return _owner; }
protected:
	Object* _owner;
};

