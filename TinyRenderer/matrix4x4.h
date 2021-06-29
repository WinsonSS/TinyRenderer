#pragma once
#include "vector3.h"
#include "vector4.h"
#include <initializer_list>

struct Matrix4x4
{
private:
	float data[4][4];
public:
	static const Matrix4x4 kIdentity;
	static const Matrix4x4 kZero;
	static Matrix4x4 LookAt(const Vector3 &from, const Vector3 &to, const Vector3 &up);
    static Matrix4x4 Perspective(float fov, float aspect, float z_near, float z_far);
	static Matrix4x4 Orthogonal(float left, float right, float bottom, float top, float z_near, float z_far);
	static Matrix4x4 Orthogonal(float aspect, float size, float z_near, float z_far);
	static Matrix4x4 Translate(const Vector3 &v);
	static Matrix4x4 Scale(const Vector3 &v);
	static Matrix4x4 Rotate(const Vector3 &v);
	Matrix4x4();
	Matrix4x4(const std::initializer_list<float> &list);
	Matrix4x4(const Matrix4x4 &m);
	float (&operator[](int row))[4];
	const float (&operator[](int row) const)[4];
	Matrix4x4 Inverse();
	Matrix4x4 Transpose();
	void SetRow(int row, const Vector4 &v);
	Vector4 GetRow(int row) const;
	void SetColumn(int column, const Vector4 &v);
	Vector4 GetColumn(int column) const;
	float Determinant();
	float Minor(int row, int column);
	float Cofactor(int row, int column);
	Matrix4x4 Adjugate();
	void Print() const;
};

Matrix4x4& operator*=(Matrix4x4 &lhs, float n);
Matrix4x4 operator*(Matrix4x4 lhs, float n);
Matrix4x4 operator*(float n, Matrix4x4 rhs);
Vector4 operator*(const Matrix4x4 &lhs, const Vector4 &v);
Matrix4x4 operator*(const Matrix4x4 &lhs, const Matrix4x4 &rhs);
Matrix4x4& operator/=(Matrix4x4 &lhs, float n);
Matrix4x4 operator/(Matrix4x4 lhs, float n);
bool operator==(const Matrix4x4 &lhs, const Matrix4x4 &rhs);
bool operator!=(const Matrix4x4 &lhs, const Matrix4x4 &rhs);
