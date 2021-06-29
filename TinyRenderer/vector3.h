#pragma once

struct Vector4;

struct Vector3
{
public:
	float x;
	float y;
	float z;
	static const Vector3 kZero;
	Vector3();
	Vector3(const float &a_x, const float &a_y, const float &a_z);
	Vector3(const Vector4 &v);
	float Magnitude();
	Vector3 Normalize();
	float& operator[](const int &index);
	const float& operator[](const int &index) const;
	void Print() const;
};

Vector3 operator*(Vector3 v, const float &n);

Vector3 operator*(const float &n, Vector3 v);

Vector3& operator*=(Vector3 &v, const float &n);

Vector3 operator/(Vector3 v, const float &n);

Vector3& operator/=(Vector3 &v, const float &n);

Vector3 operator*(const Vector3 &v1, const Vector3 &v2);

Vector3& operator+=(Vector3 &v1, const Vector3 &v2);

Vector3 operator+(Vector3 v1, const Vector3 &v2);

Vector3 operator-(Vector3 v);

Vector3& operator-=(Vector3 &v1, const Vector3 &v2);

Vector3 operator-(Vector3 v1, const Vector3 &v2);

bool operator==(const Vector3 &v1, const Vector3 &v2);

bool operator!=(const Vector3 &v1, const Vector3 &v2);
