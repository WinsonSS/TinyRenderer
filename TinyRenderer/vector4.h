#pragma once

struct Vector3;

struct Vector4
{
public:
	float x;
	float y;
	float z;
	float w;
	static const Vector4 kZero;
	Vector4();
	Vector4(const float& a_x, const float& a_y, const float& a_z, const float &a_w);
	Vector4(const Vector3 &v);
	float Magnitude();
	Vector4 Normalize();
	float& operator[](const int& index);
	const float& operator[](const int& index) const;
	void Print() const;
};

Vector4 operator*(Vector4 v, const float &n);

Vector4 operator*(const float &n, Vector4 v);

Vector4& operator*=(Vector4 &v, const float &n);

Vector4 operator/(Vector4 v, const float &n);

Vector4& operator/=(Vector4 &v, const float &n);

Vector4 operator*(const Vector4 &v1, const Vector4 &v2);

Vector4& operator+=(Vector4 &v1, const Vector4 &v2);

Vector4 operator+(Vector4 v1, const Vector4 &v2);

Vector4 operator-(Vector4 v);

Vector4& operator-=(Vector4 &v1, const Vector4 &v2);

Vector4 operator-(Vector4 v1, const Vector4 &v2);

bool operator==(const Vector4 &v1, const Vector4 &v2);

bool operator!=(const Vector4 &v1, const Vector4 &v2);
