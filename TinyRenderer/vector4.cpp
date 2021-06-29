#include <cstdio>
#include <cmath>
#include <cassert>
#include "vector4.h"
#include "vector3.h"

Vector4::Vector4() : x(0.f), y(0.f), z(0.f), w(0.f) {}


Vector4::Vector4(const float &a_x, const float &a_y, const float &a_z, const float &a_w) : x(a_x), y(a_y), z(a_z), w(a_w) {}


Vector4::Vector4(const Vector3 &v) : x(v.x), y(v.y), z(v.z), w(1.0f) {}


float& Vector4::operator[](const int &index)
{
	return index <= 0 ? x : (index == 1 ? y : (index == 2 ? z : w));
}


const float& Vector4::operator[](const int &index) const
{
	return index <= 0 ? x : (index == 1 ? y : (index == 2 ? z : w));
}


void Vector4::Print() const
{
#ifdef _DEBUG
	printf("Vector4{ x = %f, y = %f, z = %f, w = %f}\n", x, y, z, w);
#endif // _DEBUG
}


float Vector4::Magnitude()
{
	return std::sqrt(x*x + y*y + z*z + w*w);
}


Vector4 Vector4::Normalize()
{
	float magnitude = Magnitude();
	if (magnitude != 0)
	{
		return (*this) / magnitude;
	}
	return Vector4::kZero;
}


const Vector4 Vector4::kZero = Vector4(0.f, 0.f, 0.f, 0.f);

Vector4 operator*(Vector4 v, const float &n)
{
	return v *= n;
}

Vector4 operator*(const float &n, Vector4 v)
{
	return v *= n;
}

Vector4& operator*=(Vector4 &v, const float &n)
{
	v.x *= n;
	v.y *= n;
	v.z *= n;
	v.w *= n;
	return v;
}

Vector4 operator/(Vector4 v, const float &n)
{
	return v /= n;
}

Vector4& operator/=(Vector4 &v, const float &n)
{
#ifdef _DEBUG
	assert(n != 0);
#endif // _DEBUG
	return v *= (1 / n);
}

Vector4 operator*(const Vector4 &v1, const Vector4 &v2)
{
	Vector4 ret;
	ret.x = v1.x * v2.x;
	ret.y = v1.y * v2.y;
	ret.z = v1.z * v2.z;
	ret.w = v1.w * v2.w;
	return ret;
}

Vector4& operator+=(Vector4 &v1, const Vector4 &v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	v1.w += v2.w;
	return v1;
}

Vector4 operator+(Vector4 v1, const Vector4 &v2)
{
	return v1 += v2;
}

Vector4 operator-(Vector4 v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	v.w = -v.w;
	return v;
}

Vector4& operator-=(Vector4 &v1, const Vector4 &v2)
{
	return v1 += (-v2);
}

Vector4 operator-(Vector4 v1, const Vector4& v2)
{
	return v1 -= v2;
}

bool operator==(const Vector4 &v1, const Vector4 &v2)
{
	return v1.x == v2.x
		&& v1.y == v2.y
		&& v1.z == v2.z
		&& v1.w == v2.w;
}

bool operator!=(const Vector4 &v1, const Vector4 &v2)
{
	return !operator==(v1, v2);
}
