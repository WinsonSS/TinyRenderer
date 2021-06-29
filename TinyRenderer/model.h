#pragma once
#include <vector>
#include <string>
#include "graphic_math.h"
#include "tga_image.h"

class Model
{
private:
	Vector3 rotate_;
	Vector3 scale_;
	Vector3 position_;
	std::vector<Vector3> vertices_;
	std::vector<std::vector<Vector3>> faces_;
	std::vector<Vector3> normals_;
	std::vector<Vector2> uvs_;
	void LoadTexture(std::string file_name, const char *suffix, TGAImage &img);
public:
	Model(const char *file_name);
	~Model();
	int VertexCount();
	int FaceCount();
	TGAImage diffuse_map;
	TGAImage normal_map;
	TGAImage specular_map;
	Vector3 GetNormal(int face_idx, int vert_idx);
	Vector3 GetNormalFromNormalMap(Vector2 uvf);
	Vector3 GetVertex(int idx);
	Vector3 GetVertex(int face_idx, int vert_idx);
	Vector2 GetUV(int face_idx, int vert_idx);
	Matrix4x4 GetModelMatrix();
	void set_position(Vector3 position);
	void set_scale(Vector3 scale);
	void set_rotate(Vector3 rotate);
	TGAColor GetDiffuse(Vector2 uvf);
	float GetSpecular(Vector2 uvf);
	std::vector<int> GetFaceVertex(int idx);
};
