#include "renderer.h"
#include "game_time.h"
#include <cmath>
#include <utility>
#include <limits>
#include <algorithm>

bool Renderer::IsCullFace(Vector3 v1, Vector3 v1_normal)
{
	if (cull_mode_ == FaceCullMode::kCullNone)
	{
		return false;
	}
	Vector3 camera_pos = camera_->position();
	Vector3 view_dir = (camera_pos - v1).Normalize();
	Vector3 normal_dir = v1_normal.Normalize();
	float flag = Dot(view_dir, normal_dir);
	if (cull_mode_ == FaceCullMode::kCullBack)
	{
		return flag < 0;
	}
	return flag > 0;
}

Renderer::Renderer()
	: width_(), height_(), handle_window_(), handle_window_dc_(), handle_back_buffer_(),
	handle_back_buffer_dc_(),vertices_(nullptr), normals_(nullptr), triangles_(nullptr),
	camera_(nullptr), model_matrix_(Matrix4x4::kIdentity), view_matrix_(), projection_matrix_(),
	cull_mode_(FaceCullMode::kCullNone)
{

}


Renderer::~Renderer()
{

}


void Renderer::Init(HWND handle_window, const int &width, const int &height)
{
	width_ = width;
	height_ = height;
	handle_window_ = handle_window;
	handle_window_dc_ = GetDC(handle_window_);
	handle_back_buffer_ = CreateCompatibleBitmap(handle_window_dc_, width, height);
	handle_back_buffer_dc_ = CreateCompatibleDC(handle_window_dc_);
	SelectObject(handle_back_buffer_dc_, handle_back_buffer_);
}


void Renderer::Release()
{
	ReleaseDC(handle_window_, handle_window_dc_);
	DeleteDC(handle_back_buffer_dc_);
	DeleteObject(handle_back_buffer_);
}

Vector2 Renderer::ViewPort(Vector4 c)
{
	Vector2 screen_coord;
	screen_coord.x = floor((c.x / 2 + 0.5) * width_);
	screen_coord.y = floor((c.y / 2 + 0.5) * height_);
	return screen_coord;
}

void Renderer::Render()
{
	if (!CanRender())
		return;
	PrepareMatrixes();
	ClearBackBuffer(RGB(0, 0, 0));
			//clock_t start = clock();
	for (size_t i = 2; i < triangles_->size(); i += 3)
	{
		int v1_idx = (*triangles_)[i - 2];
		int v2_idx = (*triangles_)[i - 1];
		int v3_idx = (*triangles_)[i];
		Vector3 v1 = (*vertices_)[v1_idx];
		Vector3 v2 = (*vertices_)[v2_idx];
		Vector3 v3 = (*vertices_)[v3_idx];
		Vector3 v1_normal = (*normals_)[v1_idx];
		Vector3 v2_normal = (*normals_)[v2_idx];
		Vector3 v3_normal = (*normals_)[v3_idx];
		if (IsCullFace(model_matrix_ * v1, model_matrix_ * v1_normal))
		{
			continue;
		}
		COLORREF color;
		switch (i / 6)
		{
		case 0:
			color = RGB(255, 0, 0);
			break;
		case 1:
			color = RGB(0, 255, 0);
			break;
		case 2:
			color = RGB(0, 0, 255);
			break;
		case 3:
			color = RGB(255, 255, 0);
			break;
		case 4:
			color = RGB(255, 0, 255);
			break;
		case 5:
			color = RGB(0, 255, 255);
			break;
		default:
			color = RGB(233, 233, 233);
			break;
		}
		Vector4 clip_v1 = projection_matrix_ * view_matrix_ * model_matrix_ * Vector4(v1);
		Vector4 clip_v2 = projection_matrix_ * view_matrix_ * model_matrix_ * Vector4(v2);
		Vector4 clip_v3 = projection_matrix_ * view_matrix_ * model_matrix_ * Vector4(v3);
		Vector4 ndc_v1 = clip_v1 / clip_v1.w;
		Vector4 ndc_v2 = clip_v2 / clip_v2.w;
		Vector4 ndc_v3 = clip_v3 / clip_v3.w;
		ndc_v1.y = - ndc_v1.y;
		ndc_v2.y = - ndc_v2.y;
		ndc_v3.y = - ndc_v3.y;
		Vector2 screen_v1 = ViewPort(ndc_v1);
		Vector2 screen_v2 = ViewPort(ndc_v2);
		Vector2 screen_v3 = ViewPort(ndc_v3);
		if (fill_mode_ == FillMode::kLineFrame)
		{
			DrawLineFrame(screen_v1, screen_v2, screen_v3, color);
		}
		else if (fill_mode_ == FillMode::kFill)
		{
			/*
			if (v1_normal != Vector3(1, 0, 0) && v1_normal != Vector3(0, 1, 0))
				continue;
			*/
			//DrawLineFrame(screen_v1, screen_v2, screen_v3, color);
			Vector2 bound_box_min((std::numeric_limits<float>::max)(), (std::numeric_limits<float>::max)());
			Vector2 bound_box_max(-(std::numeric_limits<float>::max)(), -(std::numeric_limits<float>::max)());
			Vector2 clamp(width_ - 1, height_ - 1);
			Vector2 v2s[3];
			v2s[0] = screen_v1;
			v2s[1] = screen_v2;
			v2s[2] = screen_v3;
			for (int i = 0; i < 3; ++i)
			{
				bound_box_min[0] = (std::max)(0.f, (std::min)(bound_box_min[0], v2s[i][0]));
				bound_box_min[1] = (std::max)(0.f, (std::min)(bound_box_min[1], v2s[i][1]));
				bound_box_max[0] = (std::min)(clamp[0], (std::max)(bound_box_max[0], v2s[i][0]));
				bound_box_max[1] = (std::min)(clamp[1], (std::max)(bound_box_max[1], v2s[i][1]));
			}

			Vector2 point_p;
			for (point_p.x = bound_box_min.x; point_p.x <= bound_box_max.x; ++point_p.x)
			{
				for (point_p.y = bound_box_min.y; point_p.y <= bound_box_max.y; ++point_p.y)
				{
					Vector3 barycentric_coor = ComputeBarycentric(screen_v1, screen_v2, screen_v3, point_p);
					if (barycentric_coor.x < 0 || barycentric_coor.y < 0 || barycentric_coor.z < 0)
					{
						continue;
					}
					SetPixel(handle_back_buffer_dc_, point_p.x, point_p.y, color);
				}
			}
		}
	}
		//	printf("elapse: %d\n", clock() - start);
	BitBlt(handle_window_dc_, 0, 0, width_, height_, handle_back_buffer_dc_, 0, 0, SRCCOPY);
}


Camera *Renderer::camera()
{
	return camera_;
}

void Renderer::set_camera(Camera *camera)
{
	camera_ = camera;
}

void Renderer::set_vertices(std::vector<Vector3> *vertices)
{
	vertices_ = vertices;
}

void Renderer::set_triangles(std::vector<int> *triangles)
{
	triangles_ = triangles;
}

void Renderer::set_normals(std::vector<Vector3> *normals)
{
	normals_ = normals;
}

void Renderer::set_model_matrix(Matrix4x4 model_matrix)
{
	model_matrix_ = model_matrix;
}

FaceCullMode Renderer::cull_mode()
{
	return cull_mode_;
}

void Renderer::set_cull_mode(FaceCullMode cull_mode)
{
	cull_mode_ = cull_mode;
}

FillMode Renderer::fill_mode()
{
	return fill_mode_;
}

void Renderer::set_fill_mode(FillMode fill_mode)
{
	fill_mode_ = fill_mode;
}


void Renderer::ClearBackBuffer(COLORREF background_color)
{
	RECT rect = { 0, 0, width_, height_};
	HBRUSH hBrush = CreateSolidBrush(background_color);
	FillRect(handle_back_buffer_dc_, &rect, hBrush);
	DeleteObject(hBrush);
}

void Renderer::PrepareMatrixes()
{
	if (!camera_->IsDirty())
	{
		return;
	}
	view_matrix_ = camera_->GetViewMatrix();
	projection_matrix_ = camera_->GetProjectionMatrix();
}

bool Renderer::CanRender()
{
	return camera_ != nullptr && vertices_ != nullptr && triangles_ != nullptr && normals_ != nullptr;
}

/*
Vector3 Renderer::ComputeBarycentric(Vector2 point_a, Vector2 point_b, Vector2 point_c, Vector2 point_p)
{
	Vector2 ab = point_b - point_a;
	Vector2 ac = point_c - point_a;
	Vector2 pa = point_a - point_p;
	Vector3 uv1 = Cross(Vector3(ab.x, ac.x, pa.x), Vector3(ab.y, ac.y, pa.y));
	/*
	if (uv1[2] < 1e-4) //如果三角形为退化三角形，那么ab, ac, ac共线，那么叉积为0向量，即uv1[2]必为0
	{
		Vector3(-1, 1, 1).Print();
		printf("#################");
		//x分量为-1代表共线
		return Vector3(-1, 1, 1);
	}
	return Vector3(1.f - (uv1.x + uv1.y) / uv1.z, uv1.x / uv1.z, uv1.y / uv1.z);
}
*/
Vector3 Renderer::ComputeBarycentric(Vector2 point_a, Vector2 point_b, Vector2 point_c, Vector2 point_p)
{
	Vector3 s[2];
	for (int i = 2; i--; ) {
		s[i][0] = point_c[i] - point_a[i];
		s[i][1] = point_b[i] - point_a[i];
		s[i][2] = point_a[i] - point_p[i];
	}
	Vector3 u = Cross(s[0], s[1]);
	if (std::abs(u[2]) > 1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
		return Vector3(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
	return Vector3(-1, 1, 1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}

void Renderer::DrawLine(Vector2 point_a, Vector2 point_b, COLORREF color)
{
	bool is_steep = false;
	if (std::abs(point_a.x - point_b.x) < std::abs(point_a.y - point_b.y))
	{
		std::swap(point_a.x, point_a.y);
		std::swap(point_b.x, point_b.y);
		is_steep = true;
	}
	if (point_a.x > point_b.x)
	{
		Vector2 temp = point_a;
		point_a = point_b;
		point_b = temp;
	}
	int diff_x = point_b.x - point_a.x;
	int diff_y = point_b.y - point_a.y;

	for (int x = point_a.x; x <= point_b.x; ++x)
	{
		float factor = (x - point_a.x) / (float)diff_x;
		int y = point_a.y + diff_y * factor;
		if (is_steep)
		{
			SetPixel(handle_back_buffer_dc_, y, x, color);
		}
		else
		{
			SetPixel(handle_back_buffer_dc_, x, y, color);
		}
	}
}

void Renderer::DrawLineFrame(Vector2 point_a, Vector2 point_b, Vector2 point_c, COLORREF color)
{
	DrawLine(point_a, point_b, color);
	DrawLine(point_a, point_c, color);
	DrawLine(point_b, point_c, color);
}
