#include <cstdio>
#include <cmath>
#include <cassert>
#include "vector3.h"
#include "vector4.h"

Vector3::Vector3() : x(0.f), y(0.f), z(0.f) {}


Vector3::Vector3(const float &a_x, const float &a_y, const float &a_z) : x(a_x), y(a_y), z(a_z) {}


Vector3::Vector3(const Vector4 &v) : x(v.x), y(v.y), z(v.z) {}


float& Vector3::operator[](const int &index)
{
	return index <= 0 ? x : (index <= 1 ? y : z);
}


const float& Vector3::operator[](const int &index) const
{
	return index <= 0 ? x : (index <= 1 ? y : z);
}


void Vector3::Print() const
{
#ifdef _DEBUG
	printf("Vector3{ x = %f, y = %f, z = %f}\n", x, y, z);
#endif // _DEBUG
}


float Vector3::Magnitude()
{
	return std::sqrt(x*x + y*y + z*z);
}


Vector3 Vector3::Normalize()
{
	float magnitude = Magnitude();
	if (magnitude != 0)
	{
		return (*this) / magnitude;
	}
	return Vector3::kZero;
}


const Vector3 Vector3::kZero = Vector3(0.f, 0.f, 0.f);

Vector3 operator*(Vector3 v, const float &n)
{
	return v *= n;
}

Vector3 operator*(const float &n, Vector3 v)
{
	return v *= n;
}

Vector3& operator*=(Vector3 &v, const float &n)
{
	v.x *= n;
	v.y *= n;
	v.z *= n;
	return v;
}

Vector3 operator/(Vector3 v, const float &n)
{
	return v /= n;
}

Vector3& operator/=(Vector3 &v, const float &n)
{
#ifdef _DEBUG
	assert(n != 0);
#endif // _DEBUG
	return v *= (1 / n);
}

Vector3 operator*(const Vector3 &v1, const Vector3 &v2)
{
	Vector3 ret;
	ret.x = v1.x * v2.x;
	ret.y = v1.y * v2.y;
	ret.z = v1.z * v2.z;
	return ret;
}

Vector3& operator+=(Vector3 &v1, const Vector3 &v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}

Vector3 operator+(Vector3 v1, const Vector3 &v2)
{
	return v1 += v2;
}

Vector3 operator-(Vector3 v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return v;
}

Vector3& operator-=(Vector3 &v1, const Vector3 &v2)
{
	return v1 += (-v2);
}

Vector3 operator-(Vector3 v1, const Vector3& v2)
{
	return v1 -= v2;
}

bool operator==(const Vector3 &v1, const Vector3 &v2)
{
	return v1.x == v2.x
		&& v1.y == v2.y
		&& v1.z	== v2.z;
}

bool operator!=(const Vector3 &v1, const Vector3 &v2)
{
	return !operator==(v1, v2);
}
