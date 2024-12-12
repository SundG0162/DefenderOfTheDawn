#pragma once
#include "ResourceBase.h"
class Texture :
    public ResourceBase
{
public:
    Texture();
    virtual ~Texture();
public:
    void loadBmp(const wstring& path);
    const HDC& getTextureDC() const { return hDC; }
    const LONG& getWidth() const { return _bitInfo.bmWidth; }
    const LONG& getHeight()const { return _bitInfo.bmHeight; }
    void setTransParent(COLORREF transparent) { _transparent = transparent; }
    const COLORREF& getTransparent() { return _transparent; }
private:
    HDC hDC = {};
    HBITMAP _hBitmap = {};
    BITMAP  _bitInfo = {};
    COLORREF _transparent = RGB(255, 0, 255); // Åõ¸íÃ³¸® ¹«½¼»ö±ò
};