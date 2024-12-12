#include "pch.h"
#include "Object.h"
#include "SpriteRenderer.h"
#include "Core.h"
#include "Sprite.h"
#include <format>

SpriteRenderer::SpriteRenderer()
	: _sprite(nullptr)
	, _scale{ 1,1 }
	, _offset{ 0, 0 }
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::lateUpdate()
{
}

void SpriteRenderer::render(HDC hDC)
{
    if (_sprite == nullptr) return;

    Vector2 pos = _owner->getPosition();
    Vector2 size = _sprite->getSize();
    Vector2 scaledSize = _scale * _sprite->getSize();
    TransparentBlt(hDC,
        pos.x - scaledSize.x / 2 + _offset.x,
        pos.y - scaledSize.y / 2 + _offset.y,
        scaledSize.x, scaledSize.y,
        _sprite->getSpriteDC(),
        0, 0,
        size.x, size.y,
        _sprite->getTransparent());

    if (_whiteness)
    {
        BITMAP info;
        HBITMAP spriteBitmap = _sprite->getSpriteBitmap();
        GetObject(spriteBitmap, sizeof(BITMAP), &info);
        vector<BYTE> bits(info.bmWidthBytes * info.bmHeight);
        GetBitmapBits(spriteBitmap, bits.size(), bits.data());
        for (int y = 0; y < scaledSize.y; y++)
        {
            for (int x = 0; x < scaledSize.x; x++)
            {
                int sourceX = x * size.x / scaledSize.x;
                int sourceY = y * size.y / scaledSize.y;
                COLORREF pixelColor;

                BYTE* byte = &bits[sourceY * info.bmWidthBytes + sourceX * 3];

                pixelColor = RGB(byte[2], byte[1], byte[0]);

                if (pixelColor != _sprite->getTransparent())
                {
                    SetPixel(hDC, pos.x - scaledSize.x / 2 + x, pos.y - scaledSize.y / 2 + y, RGB(255, 255, 255));
                }
            }
        }
    }
}