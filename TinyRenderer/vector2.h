#pragma once
struct Vector3;
struct Vector4;

struct Vector2
{
public:
	float x;
	float y;
	static const Vector2 kZero;
	Vector2();
	Vector2(const float &a_x, const float &a_y);
	Vector2(const Vector3 &v);
	Vector2(const Vector4 &v);
	float Magnitude();
	Vector2 Normalize();
	float& operator[](const int &index);
	const float& operator[](const int &index) const;
	void Print() const;
};

Vector2 operator*(Vector2 v, const float &n);

Vector2 operator*(const float &n, Vector2 v);

Vector2& operator*=(Vector2 &v, const float &n);

Vector2 operator/(Vector2 v, const float &n);

Vector2& operator/=(Vector2 &v, const float &n);

Vector2 operator*(const Vector2 &v1, const Vector2 &v2);

Vector2& operator+=(Vector2 &v1, const Vector2 &v2);

Vector2 operator+(Vector2 v1, const Vector2 &v2);

Vector2 operator-(Vector2 v);

Vector2& operator-=(Vector2 &v1, const Vector2 &v2);

Vector2 operator-(Vector2 v1, const Vector2 &v2);

bool operator==(const Vector2 &v1, const Vector2 &v2);

bool operator!=(const Vector2 &v1, const Vector2 &v2);
