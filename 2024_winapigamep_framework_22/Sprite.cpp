#include "pch.h"
#include "Sprite.h"
#include "Texture.h"
#include "ResourceManager.h"

Sprite::Sprite(Texture* texture, int32 x, int32 y, int32 cx, int32 cy)
	: _texture(texture)
	, _x(x)
	, _y(y)
	, _cx(cx)
	, _cy(cy)
{
	HDC textureDC = _texture->getTextureDC();
	_hSpriteDC = CreateCompatibleDC(textureDC);
	_hSpriteBitmap = CreateCompatibleBitmap(textureDC, _cx, _cy);
	SelectObject(_hSpriteDC, _hSpriteBitmap);
	BitBlt(_hSpriteDC, 0, 0, _cx, _cy, textureDC, _x, _y, SRCCOPY);
}



Sprite::~Sprite()
{
	DeleteObject(_hSpriteBitmap);
	DeleteDC(_hSpriteDC);
}

const int32& Sprite::getTransparent()
{
	return _texture->getTransparent();
}
