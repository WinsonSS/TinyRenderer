#include "graphic_math.h"

Vector3 Cross(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

float Dot(const Vector2 &v1, const Vector2 &v2)
{
	return v1.x * v2.x
		 + v1.y * v2.y;
}

float Dot(const Vector3 &v1, const Vector3 &v2)
{
	return v1.x * v2.x
		 + v1.y * v2.y
		 + v1.z * v2.z;
}

float Dot(const Vector4 &v1, const Vector4 &v2)
{
	return v1.x * v2.x 
		 + v1.y * v2.y 
		 + v1.z * v2.z 
		 + v1.w * v2.w;
}
