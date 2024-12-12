#pragma once
class GDISelector
{
public:
	GDISelector(HDC hDC, PEN_TYPE _ePen);
	GDISelector(HDC hDC, BRUSH_TYPE _eBrush);
	GDISelector(HDC hDC, HFONT _font);
	~GDISelector();
private:
	HDC		hDC;
	HPEN	_hDefaultPen;
	HBRUSH	_hDefaultBrush;
	HFONT   _hDefaultFont;
	HFONT	_hFont;
};
