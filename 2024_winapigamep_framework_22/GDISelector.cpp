#include "pch.h"
#include "GDISelector.h"
#include "Core.h"
GDISelector::GDISelector(HDC hDC, PEN_TYPE _ePen)
	: hDC(hDC)
	, _hDefaultBrush(nullptr)
	, _hDefaultPen(nullptr)
	, _hDefaultFont(nullptr)
	, _hFont(nullptr)
{
	HPEN hColorPen = Core::getInstance()->getPen(_ePen);
	_hDefaultPen = (HPEN)SelectObject(hDC, hColorPen);
}

GDISelector::GDISelector(HDC hDC, BRUSH_TYPE _eBrush)
	: hDC(hDC)
	, _hDefaultBrush(nullptr)
	, _hDefaultPen(nullptr)
	, _hDefaultFont(nullptr)
	, _hFont(nullptr)
{
	HBRUSH hColorBrush = Core::getInstance()->getBrush(_eBrush);
	_hDefaultBrush = (HBRUSH)SelectObject(hDC, hColorBrush);
}

GDISelector::GDISelector(HDC hDC, HFONT _font)
	: hDC(hDC)
	, _hDefaultBrush(nullptr)
	, _hDefaultPen(nullptr)
	, _hDefaultFont(nullptr)
	, _hFont(nullptr)
{
	_hFont = _font;
	_hDefaultFont = (HFONT)SelectObject(hDC, _hFont);
	SetBkMode(hDC, TRANSPARENT);
}

GDISelector::~GDISelector()
{
	SelectObject(hDC, _hDefaultPen);
	SelectObject(hDC, _hDefaultBrush);
	SelectObject(hDC, _hDefaultFont);
}

