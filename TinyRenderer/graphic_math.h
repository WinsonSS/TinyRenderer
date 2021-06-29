#pragma once
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4x4.h"

Vector3 Cross(const Vector3& v1, const Vector3& v2);
float Dot(const Vector2& v1, const Vector2& v2);
float Dot(const Vector3& v1, const Vector3& v2);
float Dot(const Vector4& v1, const Vector4& v2);
