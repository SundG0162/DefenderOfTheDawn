#include "pch.h"
#include "CopyWindow.h"

CopyWindow::CopyWindow(const Vector2& position, const Vector2& size, const wstring& name) : Window(position, size, name)
{
}

CopyWindow::~CopyWindow()
{
}

void CopyWindow::render(HDC hdc)
{
    BitBlt(_hMainDC, 0, 0, _size.x, _size.y, hdc, _leftTopPosition.x, _leftTopPosition.y, SRCCOPY);
}