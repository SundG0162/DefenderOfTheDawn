#pragma once
#include <random>
#include <iostream>
class Sprite;
class Texture;
namespace utils
{
	static const float PI = 3.141592f;
	class SpriteParser
	{
	public:
		static Sprite* textureToSprite(Texture* texture);
		static Sprite* textureToSprite(Texture* texture, Vector2 leftTop, Vector2 sliceSize);
		static vector<Sprite*> textureToSprites(Texture* texture, Vector2 leftTop, Vector2 sliceSize, Vector2 step);
		static vector<Sprite*> textureToSprites(Texture* texture, Vector2 leftTop, Vector2 sliceSize, int step);
	};	
	class Drawer
	{
	public:
		static void renderText(HDC hdc, Vector pos, const wstring& str);
		static void renderRect(HDC hdc, Vector pos, int32 width, int32 height);
		static void renderRectColor(HDC hdc, Vector pos, int32 width, int32 height, COLORREF brushColor, COLORREF penColor);
		static void renderCircle(HDC hdc, Vector pos, int32 radius);
		static void renderCircleColor(HDC hdc, Vector pos, int32 radius, COLORREF brushColor, COLORREF penColor);
		static void renderLine(HDC hdc, Vector from, Vector to);
		static void renderLineColor(HDC hdc, Vector from, Vector to, COLORREF color);
	};
	class Ease
	{
	public:
		static float inSine(float x) { return 1 - cosf((x * PI) / 2); }
		static float outSine(float x) { return sinf((x * PI) / 2); }
		static float inOutSine(float x) { return -(cosf(PI * x) - 1) / 2; }
		static float inQuad(float x) { return x * x; }
		static float outQuad(float x) { return 1 - (1 - x) * (1 - x); }
		static float inOutQuad(float x) { return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2.f; }
		static float inCubic(float x) { return x * x * x; }
		static float outCubic(float x) { return 1 - pow(1 - x, 3); }
		static float inOutCubic(float x) { return x < 0.5f ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2; }
	};
	class TextEditor
	{
	public:
		static vector<wstring> textSplit(const wstring& text);
	};
	class CoordinateSync
	{
	public:
		static Vector2 nonClientToClient(const RECT& windowRect, const Vector2& position);
	};
	class ExMath //ExtendedMathmatics의 줄임말, 사실상 회전행렬과 무작위값 전용 클래스
	{
	public:
		static float getRandomValue(float minValue, float maxValue); //mt써서 무작위 값 얻는 코드
		static int getRandomValue(int minValue, int maxValue); //mt써서 무작위 값 얻는 코드
		static void rotateVector(Vector2& vector, float angle) // 회전 행렬 써서 회전시킴
		{
			float x = cosf(angle)*vector.x - sinf(angle)*vector.y;
			float y = sinf(angle)*vector.x + cosf(angle)*vector.y;
			vector.x = x;
			vector.y = y;
		}
		static Vector2 getRandomVector()//위 두 코드 합친 코드 - 잘 작동하는지 확인 안함
		{
			Vector2 v = { 1,0 };
			rotateVector(v, getRandomValue(0.f, 360.f));
			return v;
		}
	};
};