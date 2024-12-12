#pragma once
#include "WindowObject.h"
class Collider;
class Enemy;
class CaptureObject : public WindowObject
{
public:
	CaptureObject(const Vector2& position, const Vector2& size, const WINDOW_TYPE& type, const wstring& name = L"");
	virtual ~CaptureObject();
public:
	void update() override;
public:
	void handleOnCollisionEnter(Collider* other);
	void handleOnCollisionStay(Collider* other);
	void handleOnCollisionExit(Collider* other);
protected:
	vector<Enemy*> _targets;
	vector<Enemy*> _temp;
	Collider* _collider;
};

