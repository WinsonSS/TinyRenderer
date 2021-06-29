#pragma once
#include "camera.h"
class OrthogonalCamera : public Camera
{
private:
	float size_;
	void ComputeMatrixes() override;
	Matrix4x4 projection_matrix_;
public:
	OrthogonalCamera();
	float size();
	void set_size(float size);
	Matrix4x4 GetProjectionMatrix() override;
	CameraProjectionType GetProjectionType() override;
};

