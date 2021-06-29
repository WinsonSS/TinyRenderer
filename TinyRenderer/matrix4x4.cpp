#include "matrix4x4.h"
#include "graphic_math.h"
#include <cassert>
#include <cstdio>
#include <sstream>

const float kDegreeToRadius = std::acos(-1) / 180;

Matrix4x4::Matrix4x4() :data()
{

}


Matrix4x4::Matrix4x4(const std::initializer_list<float> &list) : data()
{
	int size = 16;
	if (list.size() < 16)
	{
		size = list.end() - list.begin();
	}
	auto it = list.begin();
	for (int i = 0; i < size; ++i)
	{
		data[i / 4][i % 4] = *(it + i);
	}
	for (int i = size; i < 16; ++i)
	{
		data[i / 4][i % 4] = 0;
	}
}


Matrix4x4::Matrix4x4(const Matrix4x4 &m) : data()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			data[i][j] = m[i][j];
		}
	}
}


float(&Matrix4x4::operator[](int row))[4]
{
#ifdef _DEBUG
	assert(row < 4);
#endif // _DEBUG
	return data[row];
}

const float(&Matrix4x4::operator[](int row) const)[4]
{
#ifdef _DEBUG
	assert(row < 4);
#endif // _DEBUG
	return data[row];
}

void Matrix4x4::SetRow(int row, const Vector4 &v)
{
	for (int i = 0; i < 4; ++i)
		data[row][i] = v[i];
}

Vector4 Matrix4x4::GetRow(int row) const
{
	Vector4 v;
	for (int i = 0; i < 4; ++i)
		v[i] = data[row][i];
	return v;
}

void Matrix4x4::SetColumn(int column, const Vector4 &v)
{
	for (int i = 0; i < 4; ++i)
		data[i][column] = v[i];
}

Vector4 Matrix4x4::GetColumn(int column) const
{
	Vector4 v;
	for (int i = 0; i < 4; ++i)
		v[i] = data[i][column];
	return v;
}

float Matrix4x4::Determinant()
{
	Matrix4x4 adjugate = Adjugate();
	return Dot(GetRow(0), adjugate.GetColumn(0));
}

float Matrix4x4::Minor(int row, int column)
{
	float m[3][3];
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			m[i][j] = data[i < row ? i : i + 1][j < column ? j : j + 1];
		}
	}
	float minor = m[0][0] * m[1][1] * m[2][2] 
				+ m[0][1] * m[1][2] * m[2][0]
				+ m[0][2] * m[1][0] * m[2][1]
				- m[0][0] * m[1][2] * m[2][1]
				- m[0][1] * m[1][0] * m[2][2]
				- m[0][2] * m[1][1] * m[2][0];
	return minor;
}

float Matrix4x4::Cofactor(int row, int column)
{
	return Minor(row, column) * ((row + column) % 2 ? -1 : 1);
}

Matrix4x4 Matrix4x4::Adjugate()
{
	Matrix4x4 ret;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			ret[i][j] = Cofactor(j, i);
		}
	}
	return ret;
}

void Matrix4x4::Print() const
{
#ifdef _DEBUG
	std::stringstream ss;
	ss << "Matrix4x4{" << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			ss << data[i][j];
			if (j < 3)
			{
				ss << ", ";
			}
			else
			{
				ss << std::endl;
			}
		}
	}
	ss << "}" << std::endl;
	printf(ss.str().c_str());
#endif // _DEBUG
}

Matrix4x4 Matrix4x4::Inverse()
{
	Matrix4x4 adjugate = Adjugate();
	float determinant = Determinant();
	return adjugate / determinant;
}

Matrix4x4 Matrix4x4::Transpose()
{
	Matrix4x4 transpose;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			transpose[i][j] = data[j][i];
		}
	}
	return transpose;
}

Matrix4x4 &operator*=(Matrix4x4 &lhs, float n)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			lhs[i][j] *= n;
		}
	}
	return lhs;
}

Matrix4x4 operator*(Matrix4x4 lhs, float n)
{
	return lhs *= n;
}

Matrix4x4 operator*(float n, Matrix4x4 rhs)
{
	return rhs *= n;
}

Vector4 operator*(const Matrix4x4 &lhs, const Vector4 &v)
{
	Vector4 ret;
	for (int i = 0; i < 4; ++i)
	{
		ret[i] = Dot(lhs.GetRow(i), v);
	}
	return ret;
}

Matrix4x4 operator*(const Matrix4x4 &lhs, const Matrix4x4 &rhs)
{
	Matrix4x4 ret;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			ret[i][j] = Dot(lhs.GetRow(i), rhs.GetColumn(j));
		}
	}
	return ret;
}

Matrix4x4 &operator/=(Matrix4x4 &lhs, float n)
{
#ifdef _DEBUG
	assert(n != 0);
#endif // _DEBUG
	return lhs *= (1 / n);
}

Matrix4x4 operator/(Matrix4x4 lhs, float n)
{
	return lhs /= n;
}

bool operator==(const Matrix4x4 &lhs, const Matrix4x4 &rhs)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (lhs[i][j] != rhs[i][j])
				return false;
		}
	}
	return true;
}

bool operator!=(const Matrix4x4 &lhs, const Matrix4x4 &rhs)
{
	return !operator==(lhs, rhs);
}

//右手坐标系视角矩阵
Matrix4x4 Matrix4x4::LookAt(const Vector3 &from, const Vector3 &to, const Vector3 &up)
{
	Vector3 forward = (to - from).Normalize();
	Vector3 right = Cross(up, forward).Normalize();
	Vector3 local_up = Cross(forward, right).Normalize();

	Matrix4x4 rotate_matrix = Matrix4x4::kIdentity;
	rotate_matrix.SetRow(0, right);
	rotate_matrix.SetRow(1, local_up);
	rotate_matrix.SetRow(2, forward);
	rotate_matrix.SetColumn(3, Vector4(0, 0, 0, 1));
	
	Matrix4x4 translate_matrix = Matrix4x4::kIdentity;
	translate_matrix.SetColumn(3, -from);

	Matrix4x4 z_negative = Matrix4x4::kIdentity;
	z_negative[2][2] = -1;

	return z_negative * rotate_matrix * translate_matrix;
}

Matrix4x4 Matrix4x4::Perspective(float fov, float aspect, float z_near, float z_far)
{
	Matrix4x4 projection;
	const float cot_1_2_fov = 1 / std::tan(fov * .5f * kDegreeToRadius);
	projection[0][0] = cot_1_2_fov / aspect;
	projection[1][1] = cot_1_2_fov;
	projection[2][2] = -(z_far + z_near) / (z_far - z_near);
	projection[2][3] = -2 * z_near * z_far / (z_far - z_near);
	projection[3][2] = -1;
	return projection;
}

Matrix4x4 Matrix4x4::Orthogonal(float left, float right, float bottom, float top, float z_near, float z_far)
{
	Matrix4x4 projection;
	projection[0][0] = 2 / (right - left);
	projection[0][3] = -(right + left) / (right - left);
	projection[1][1] = 2 / (top - bottom);
	projection[1][3] = -(top + bottom) / (top - bottom);
	projection[2][2] = -2 / (z_far - z_near);
	projection[2][3] = -(z_far + z_near) / (z_far - z_near);
	projection[3][3] = 1;
	return projection;

}

Matrix4x4 Matrix4x4::Orthogonal(float aspect, float size, float z_near, float z_far)
{
	Matrix4x4 projection;
	projection[0][0] = 1 / (aspect * size);
	projection[1][1] = 1 / size;
	projection[2][2] = -2 / (z_far - z_near);
	projection[2][3] = -(z_far + z_near) / (z_far - z_near);
	projection[3][3] = 1;
	return projection;
}

Matrix4x4 Matrix4x4::Scale(const Vector3 &v)
{
	Matrix4x4 scale_matrix = Matrix4x4::kIdentity;
	scale_matrix[0][0] *= v.x;
	scale_matrix[1][1] *= v.y;
	scale_matrix[2][2] *= v.z;
	return scale_matrix;
}

Matrix4x4 Matrix4x4::Rotate(const Vector3 &v)
{
	float rad_x = v.x * kDegreeToRadius;
	float rad_y = v.y * kDegreeToRadius;
	float rad_z = v.z * kDegreeToRadius;

	Matrix4x4 rot_x = Matrix4x4::kIdentity;
	rot_x[1][1] = std::cos(rad_x);
	rot_x[1][2] = -std::sin(rad_x);
	rot_x[2][1] = std::sin(rad_x);
	rot_x[2][2] = std::cos(rad_x);

	Matrix4x4 rot_y = Matrix4x4::kIdentity;
	rot_y[0][0] = std::cos(rad_y);
	rot_y[0][2] = std::sin(rad_y);
	rot_y[2][0] = -std::sin(rad_y);
	rot_y[2][2] = std::cos(rad_y);

	Matrix4x4 rot_z = Matrix4x4::kIdentity;
	rot_z[0][0] = std::cos(rad_z);
	rot_z[0][1] = -std::sin(rad_z);
	rot_z[1][0] = std::sin(rad_z);
	rot_z[1][1] = std::cos(rad_z);
	return rot_y * rot_x * rot_z;
}

Matrix4x4 Matrix4x4::Translate(const Vector3 &v)
{
	Matrix4x4 translate_matrix = Matrix4x4::kIdentity;
	translate_matrix.SetColumn(3, v);
	return translate_matrix;
}

const Matrix4x4 Matrix4x4::kIdentity = Matrix4x4{1, 0, 0, 0,
												0, 1, 0, 0,
												0, 0, 1, 0,
												0, 0, 0, 1};
