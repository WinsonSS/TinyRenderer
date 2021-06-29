#include "camera.h"
#include <cstdio>

Camera::Camera() : position_(Vector3::kZero), rotation_(), up_(Vector3(0, 1, 0)), aspect_(1), z_near_(1), z_far_(1000), is_dirty_(true)
{
}

Camera::~Camera()
{
}

void Camera::ComputeMatrixes()
{
	if (!is_dirty_)
	{
		return;
	}
	is_dirty_ = false;
	Vector3 dir = GetDirection();
	Vector3 target = position_ + dir;
	view_matrix_ = Matrix4x4::LookAt(position_, target, up_);
}

Matrix4x4 Camera::GetViewMatrix()
{
	ComputeMatrixes();
	return view_matrix_;
}

Vector3 Camera::position()
{
	return position_;
}

void Camera::set_position(Vector3 position)
{
	SetDirty();
	position_ = position;
}

Vector3 Camera::up()
{
	return up_;
}

void Camera::set_up(Vector3 up)
{
	SetDirty();
	up_ = up;
}

float Camera::aspect()
{
	return aspect_;
}

void Camera::set_aspect(float aspect)
{
	SetDirty();
	aspect_ = aspect;
}

float Camera::z_near()
{
	return z_near_;
}

void Camera::set_z_near(float z_near)
{
	SetDirty();
	z_near_ = z_near;
}

float Camera::z_far()
{
	return z_far_;
}

void Camera::set_z_far(float z_far)
{
	SetDirty();
	z_far_ = z_far;
}

Vector3 Camera::rotation()
{
	return rotation_;
}

void Camera::set_rotation(Vector3 rotation)
{
	SetDirty();
	rotation_ = rotation;
}

Vector3 Camera::GetDirection()
{
	Matrix4x4 rotation_matrix = Matrix4x4::Rotate(rotation_);
	return rotation_matrix * Vector3(0, 0, 1);

}

bool Camera::IsDirty()
{
	return is_dirty_;
}

void Camera::SetDirty()
{
	is_dirty_ = true;
}
