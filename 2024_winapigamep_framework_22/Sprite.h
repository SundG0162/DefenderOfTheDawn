#pragma once
#include "ResourceBase.h"
class Texture;
class Sprite : public ResourceBase
{
public:
	Sprite(Texture* texture, int32 x, int32 y, int32 cx, int32 cy);
	~Sprite();
public:
	const HDC& getSpriteDC() { return _hSpriteDC; }
	const HBITMAP& getSpriteBitmap() { return _hSpriteBitmap; }
	const Vector2& getPosition() { return Vector2(_x, _y); }
	const Vector2& getSize() { return Vector2(_cx, _cy); }
	const int32& getTransparent();
	void setPosition(Vector2 pos) { _x = pos.x; _y = pos.y; }
	void setSize(Vector2 size) { _x = size.x; _y = size.y; }
private:
	Texture* _texture = nullptr;
	int32 _x;
	int32 _y;
	int32 _cx;
	int32 _cy;

	HBITMAP _hSpriteBitmap = nullptr;
	HDC _hSpriteDC = nullptr;
};

