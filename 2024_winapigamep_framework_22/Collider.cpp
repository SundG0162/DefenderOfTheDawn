#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "GDISelector.h"
UINT Collider::_nextID = 0;
Collider::Collider()
	: _size(30.f, 30.f)
	, _position(0.f, 0.f)
	, _offset(0.f, 0.f)
	, _id(_nextID++)
{
}

Collider::~Collider()
{
}

void Collider::lateUpdate()
{
	if (!_following) return;
	Vector2 vPos = _owner->getPosition();
	_position = vPos + _offset;
}

void Collider::render(HDC hDC)
{
	/*PEN_TYPE ePen = PEN_TYPE::GREEN;
	if (_showDebug)
		ePen = PEN_TYPE::RED;
	GDISelector pen(hDC, ePen);
	GDISelector brush(hDC, BRUSH_TYPE::HOLLOW);
	RECT_render(hDC, _position.x, _position.y,
		_size.x, _size.y);*/
}

void Collider::enterCollision(Collider* _other)
{
	_showDebug = true;
	OnCollisionEnterEvent.invoke(_other);
}

void Collider::stayCollision(Collider* _other)
{
	OnCollisionStayEvent.invoke(_other);
}

void Collider::exitCollision(Collider* _other)
{
	_showDebug = false;
	OnCollisionExitEvent.invoke(_other);
}
