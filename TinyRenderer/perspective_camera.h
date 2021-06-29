#pragma once
#include "camera.h"

class PerspectiveCamera : public Camera
{
private:
	float fov_;
	void ComputeMatrixes() override;
	Matrix4x4 projection_matrix_;
public:
	PerspectiveCamera();
	float fov();
	void set_fov(float fov);
	Matrix4x4 GetProjectionMatrix() override;
	CameraProjectionType GetProjectionType() override;
};

