#include "pch.h"
#include "CaptureObject.h"
#include "Collider.h"
#include "Enemy.h"

CaptureObject::CaptureObject(const Vector2& position, const Vector2& size, const WINDOW_TYPE& type, const wstring& name) : WindowObject(position, size, type, name)
{
	_collider = addComponent<Collider>();
	_collider->setSize(size);
	_collider->OnCollisionEnterEvent += [this](Collider* other) {this->handleOnCollisionEnter(other); };
	_collider->OnCollisionStayEvent += [this](Collider* other) {this->handleOnCollisionStay(other); };
	_collider->OnCollisionExitEvent += [this](Collider* other) {this->handleOnCollisionExit(other); };
}

CaptureObject::~CaptureObject()
{
	_collider->OnCollisionEnterEvent -= [this](Collider* other) {this->handleOnCollisionEnter(other); };
	_collider->OnCollisionStayEvent -= [this](Collider* other) {this->handleOnCollisionStay(other); };
	_collider->OnCollisionExitEvent -= [this](Collider* other) {this->handleOnCollisionExit(other); };
}

void CaptureObject::update()
{
	for (int i = 0; i < _targets.size(); i++)
	{
		Enemy* enemy = _targets[i];
		vector<Enemy*>::iterator iter = std::find(_temp.begin(), _temp.end(), enemy);

		if (iter == _temp.end())
		{
			_targets.erase(std::find(_targets.begin(), _targets.end(), enemy));
		}
		else
		{
			Enemy* e = *iter;
			if (e->isDead())
			{
				_targets.erase(std::find(_targets.begin(), _targets.end(), enemy));
			}
		}
	}
	_temp.clear();
}

void CaptureObject::handleOnCollisionEnter(Collider* other)
{
	Object* obj = other->getOwner();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	if (enemy)
	{
		_targets.push_back(enemy);
		_temp.push_back(enemy);
	}
}

void CaptureObject::handleOnCollisionStay(Collider* other)
{
	Object* obj = other->getOwner();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	if (enemy)
	{
		_temp.push_back(enemy);
	}
}

void CaptureObject::handleOnCollisionExit(Collider* other)
{
	Object* obj = other->getOwner();
	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	if (enemy)
	{
		auto iter = std::find(_targets.begin(), _targets.end(), enemy);
		if (iter != _targets.end())
		{
			_targets.erase(iter);
		}
	}
}