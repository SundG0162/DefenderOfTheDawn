#include "pch.h"
#include "Texture.h"
#include "Core.h"

Texture::Texture()
{
}

Texture::~Texture()
{
	DeleteDC(hDC);
	DeleteObject(_hBitmap);
}

void Texture::loadBmp(const wstring& path)
{
	_hBitmap = (HBITMAP)LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	hDC = CreateCompatibleDC(GET_SINGLETON(Core)->getMainDC());
	if (_hBitmap == nullptr)
		MessageBox(GET_SINGLETON(Core)->getHWnd(), path.c_str(), L"Fail to Load Image", MB_OK);
	SelectObject(hDC, _hBitmap);
	GetObject(_hBitmap, sizeof(BITMAP), &_bitInfo);
}