#include "perspective_camera.h"

void PerspectiveCamera::ComputeMatrixes()
{
	if (!IsDirty())
	{
		return;
	}

	Camera::ComputeMatrixes();
	projection_matrix_ = Matrix4x4::Perspective(fov_, aspect_, z_near_, z_far_);
}

PerspectiveCamera::PerspectiveCamera() : Camera(), fov_(45.f)
{
}

float PerspectiveCamera::fov()
{
	return fov_;
}

void PerspectiveCamera::set_fov(float fov)
{
	SetDirty();
	fov_ = fov;
}

Matrix4x4 PerspectiveCamera::GetProjectionMatrix()
{
	ComputeMatrixes();
	return projection_matrix_;
}

CameraProjectionType PerspectiveCamera::GetProjectionType()
{
	return CameraProjectionType::kPerspective;
}
