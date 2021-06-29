#include <cstdio>
#include <cmath>
#include <cassert>
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

Vector2::Vector2() : x(0.f), y(0.f) {}


Vector2::Vector2(const float &a_x, const float &a_y) : x(a_x), y(a_y) {}

Vector2::Vector2(const Vector3 &v) : x(v.x), y(v.y) {}

Vector2::Vector2(const Vector4 &v) : x(v.x), y(v.y) {}


float& Vector2::operator[](const int &index)
{
	return index <= 0 ? x : y;
}


const float& Vector2::operator[](const int& index) const
{
	return index <= 0 ? x : y;
}


void Vector2::Print() const
{
#ifdef _DEBUG
	printf("Vector2{ x = %f, y = %f}\n", x, y);
#endif // _DEBUG
}


float Vector2::Magnitude()
{
	return std::sqrt(x * x + y * y);
}


Vector2 Vector2::Normalize()
{
	float magnitude = Magnitude();
	if (magnitude != 0)
	{
		return (*this) / magnitude;
	}
	return Vector2::kZero;
}


const Vector2 Vector2::kZero = Vector2(0.f, 0.f);

Vector2 operator*(Vector2 v, const float &n)
{
	return v *= n;
}

Vector2 operator*(const float& n, Vector2 v)
{
	return v *= n;
}

Vector2& operator*=(Vector2& v, const float& n)
{
	v.x *= n;
	v.y *= n;
	return v;
}

Vector2 operator/(Vector2 v, const float& n)
{
	return v /= n;
}

Vector2& operator/=(Vector2& v, const float& n)
{
#ifdef _DEBUG
	assert(n != 0);
#endif // _DEBUG

	return v *= (1 / n);
}

Vector2 operator*(const Vector2& v1, const Vector2& v2)
{
	Vector2 ret;
	ret.x = v1.x * v2.x;
	ret.y = v1.y * v2.y;
	return ret;
}

Vector2& operator+=(Vector2 &v1, const Vector2 &v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}

Vector2 operator+(Vector2 v1, const Vector2 &v2)
{
	return v1 += v2;
}

Vector2 operator-(Vector2 v)
{
	v.x = -v.x;
	v.y = -v.y;
	return v;
}

Vector2& operator-=(Vector2 &v1, const Vector2 &v2)
{
	return v1 += (-v2);
}

Vector2 operator-(Vector2 v1, const Vector2& v2)
{
	return v1 -= v2;
}

bool operator==(const Vector2 &v1, const Vector2 &v2)
{
	return v1.x == v2.x && v1.y == v2.y;
}

bool operator!=(const Vector2 &v1, const Vector2 &v2)
{
	return !operator==(v1, v2);
}
