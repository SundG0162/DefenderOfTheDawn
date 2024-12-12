#pragma once
#include<assert.h>
struct Vector
{
    Vector() {}
    Vector(float _x, float _y) : x(_x), y(_y) {}
    Vector(int _x, int _y) : x(_x), y(_y) {}
    Vector(POINT pt) : x((float)pt.x), y((float)pt.y) {}
    Vector operator+(const Vector& other)
    {
        Vector ret;
        ret.x = x + other.x;
        ret.y = y + other.y;
        return ret;
    }
    Vector operator-(const Vector& other)
    {
        Vector ret;
        ret.x = x - other.x;
        ret.y = y - other.y;
        return ret;
    }
    Vector operator*(float value)
    {
        Vector ret;
        ret.x = x * value;
        ret.y = y * value;
        return ret;
    }
    Vector operator/(float value)
    {
        Vector ret;
        ret.x = x / value;
        ret.y = y / value;
        return ret;
    }

    Vector operator*(const Vector& other)
    {
        Vector ret;
        ret.x = other.x * x;
        ret.y = other.y * y;
        return ret;
    }
    void operator+=(const Vector& other)
    {
        x += other.x;
        y += other.y;
    }
    void operator-=(const Vector& other)
    {
        x -= other.x;
        y -= other.y;
    }
    void operator*=(float value)
    {
        x *= value;
        y *= value;
    }
    float LengthSquared()
    {
        return x * x + y * y;
    }
    float Length()
    {
        return ::sqrt(LengthSquared());
    }
    void Normalize()
    {
        float len = Length();
        if (len < FLT_EPSILON)
            return;
        x /= len;
        y /= len;
    }
    float Dot(Vector other)
    {
        return x * other.x + y * other.y;
    }
    float Cross(Vector other)
    {
        return x * other.y - y * other.x;
    }
    float x = 0.f;
    float y = 0.f;
};
using Vector2 = Vector;