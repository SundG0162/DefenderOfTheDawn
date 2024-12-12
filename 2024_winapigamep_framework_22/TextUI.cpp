#include "pch.h"
#include "TextUI.h"
#include "GDISelector.h"
#include "Core.h"

TextUI::TextUI() : UI()
{
	_hFont = nullptr;
	_color = RGB(255, 255, 255);
	_text = L"";
}

TextUI::~TextUI()
{
}

void TextUI::setupFont(float fontSize, const wstring& fontName, float fontWeight)
{
	_hFont = CreateFontW(fontSize, 0, 0, 0, 0, 0, 0, 0
		, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, fontName.c_str());
}

Vector2 TextUI::getTextSize()
{
	vector<wstring> lines = utils::TextEditor::textSplit(_text);
	SIZE size = {};
	std::sort(lines.begin(), lines.end(), [](wstring& str1, wstring& str2) { return str1.size() > str2.size(); });
	HDC hdc = GET_SINGLETON(Core)->getBackDC();
	HFONT prev = (HFONT)SelectObject(hdc, _hFont);
	GetTextExtentPoint(hdc, lines[0].c_str(), lines[0].size(), &size);
	SelectObject(hdc, prev);
	int y = size.cy * lines.size();
	Vector2 textSize = { size.cx,  y };
	return textSize;
}

void TextUI::update()
{
}

void TextUI::render(HDC hdc)
{
	if (_text == L"") return;
	HFONT prevFont = (HFONT)SelectObject(hdc, _hFont);
	SetBkColor(hdc, TRANSPARENT);
	COLORREF prevColor = SetTextColor(hdc, _color);
	vector<wstring> lines = utils::TextEditor::textSplit(_text);
	GetTextExtentPoint(hdc, lines[0].c_str(), lines[0].size(), &_size);
	for (int i = 0; i < lines.size(); i++)
	{
		TextOut(hdc, _position.x - _size.cx / 2, _position.y + _size.cy * i, lines[i].c_str(), lines[i].length());
	}
	SetTextColor(hdc, prevColor);
	SelectObject(hdc, prevFont);
}