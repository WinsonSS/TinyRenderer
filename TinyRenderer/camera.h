#pragma once
#include "graphic_math.h"

enum class CameraProjectionType
{
	kOrthogonal,
	kPerspective
};

class Camera
{
protected:
	Vector3 position_;
	Vector3 up_;
	float aspect_;
	float z_near_;
	float z_far_;
	bool is_dirty_;
	Vector3 rotation_;
	Matrix4x4 view_matrix_;
	void SetDirty();
	virtual void ComputeMatrixes();
public:
	Camera();
	virtual ~Camera();
	Vector3 position();
	void set_position(Vector3 position);
	Vector3 up();
	void set_up(Vector3 up);
	float aspect();
	void set_aspect(float aspect);
	float z_near();
	void set_z_near(float z_near);
	float z_far();
	void set_z_far(float z_far);
	Vector3 rotation();
	void set_rotation(Vector3 rotation);
	Vector3 GetDirection();
	bool IsDirty();
	Matrix4x4 GetViewMatrix();
	virtual Matrix4x4 GetProjectionMatrix() = 0;
	virtual CameraProjectionType GetProjectionType() = 0;
};

