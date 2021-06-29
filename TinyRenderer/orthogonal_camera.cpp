#include "orthogonal_camera.h"

void OrthogonalCamera::ComputeMatrixes()
{
	if (!IsDirty())
	{
		return;
	}
	Camera::ComputeMatrixes();
	projection_matrix_ = Matrix4x4::Orthogonal(aspect_, size_, z_near_, z_far_);
}

OrthogonalCamera::OrthogonalCamera() : size_(1)
{
}

float OrthogonalCamera::size()
{
	return size_;
}

void OrthogonalCamera::set_size(float size)
{
	SetDirty();
	size_ = size;
}

Matrix4x4 OrthogonalCamera::GetProjectionMatrix()
{
	ComputeMatrixes();
	return projection_matrix_;
}

CameraProjectionType OrthogonalCamera::GetProjectionType()
{
	return CameraProjectionType::kOrthogonal;
}
