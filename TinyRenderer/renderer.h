#pragma once
#include "singleton.h"
#include <Windows.h>
#include "graphic_math.h"
#include "camera.h"
#include <vector>

enum class FaceCullMode
{
	kCullNone,
	kCullBack,
	kCullFront
};

enum class FillMode
{
	kLineFrame,
	kFill
};

class Renderer
{
private:
	friend class Singleton<Renderer>;
	int width_;
	int height_;
	HWND handle_window_;
	HDC handle_window_dc_;
	HBITMAP handle_back_buffer_;
	HDC handle_back_buffer_dc_;
	std::vector<Vector3> *vertices_;
	std::vector<int> *triangles_;
	std::vector<Vector3> *normals_;
	Camera *camera_;
	Matrix4x4 model_matrix_;
	Matrix4x4 view_matrix_;
	Matrix4x4 projection_matrix_;
	FaceCullMode cull_mode_;
	FillMode fill_mode_;
	bool IsCullFace(Vector3 v1, Vector3 v1_normal);
	Renderer();
	~Renderer();
	void ClearBackBuffer(COLORREF background_color);
	void PrepareMatrixes();
	bool CanRender();
	Vector3 ComputeBarycentric(Vector2 point_a, Vector2 point_b, Vector2 point_c, Vector2 point_p);
	void DrawLine(Vector2 point_a, Vector2 point_b, COLORREF color = RGB(255, 255, 255));
	void DrawLineFrame(Vector2 point_a, Vector2 point_b, Vector2 point_c, COLORREF color = RGB(255, 255, 255));
	Vector2 ViewPort(Vector4 c);
public:
	void Init(HWND handle_window, const int &width, const int &height);
	void Release();
	void Render();
	Camera *camera();
	void set_camera(Camera *camera);
	void set_vertices(std::vector<Vector3> *vertices);
	void set_triangles(std::vector<int> *triangles);
	void set_normals(std::vector<Vector3> *normals);
	void set_model_matrix(Matrix4x4 model_matrix);
	FaceCullMode cull_mode();
	void set_cull_mode(FaceCullMode cull_mode);
	FillMode fill_mode();
	void set_fill_mode(FillMode fill_mode);
};

