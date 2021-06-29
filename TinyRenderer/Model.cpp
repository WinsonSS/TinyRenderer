#include "model.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

Model::Model(const char *file_name) : rotate_(), scale_({ 1, 1, 1 }), position_(), vertices_(), faces_(), normals_(), uvs_(), diffuse_map(), normal_map(), specular_map()
{
	std::cout << "Init Model" << std::endl;
	std::ifstream file(file_name, std::ifstream::in);
	if (file.fail())
		return;
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line.c_str());
		char char_filter;
		if (!line.compare(0, 2, "v "))
		{
			ss >> char_filter;
			Vector3 v;
			for (int i = 0; i < 3; ++i)
			{
				ss >> v[i];
			}
			vertices_.push_back(v);
		}
		else if (!line.compare(0, 3, "vn "))
		{
			ss >> char_filter >> char_filter;
			Vector3 n;
			for (int i = 0; i < 3; ++i)
			{
				ss >> n[i];
			}
			normals_.push_back(n);
		}
		else if (!line.compare(0, 3, "vt "))
		{
			ss >> char_filter >> char_filter;
			Vector2 uv;
			for (int i = 0; i < 2; ++i)
			{
				ss >> uv[i];
			}
			uvs_.push_back(uv);
		}
		else if (!line.compare(0, 2, "f "))
		{
			std::vector<Vector3> face;
			Vector3 temp;
			ss >> char_filter;
			while (ss >> temp[0] >> char_filter >> temp[1] >> char_filter >> temp[2])
			{
				for (int i = 0; i < 3; ++i)
				{
					--temp[i];
				}
				face.push_back(temp);
			}
			faces_.push_back(face);
		}
	}
	LoadTexture(file_name, "_diffuse.tga", diffuse_map);
	LoadTexture(file_name, "_spec.tga", specular_map);
	LoadTexture(file_name, "_nm.tga", normal_map);
	std::cout << "Init Complete!!" << std::endl;
}

Model::~Model() {}

int Model::VertexCount()
{
	return vertices_.size();
}

int Model::FaceCount()
{
	return faces_.size();
}

Vector3 Model::GetNormal(int face_idx, int vert_idx)
{
	int normal_idx = faces_[face_idx][vert_idx][2];
	return normals_[normal_idx].Normalize();
}

Vector3 Model::GetNormalFromNormalMap(Vector2 uvf)
{
	Vector2 uv(uvf[0] * normal_map.get_width(), uvf[1] * normal_map.get_height());
	TGAColor c = normal_map.get(uv[0], uv[1]);
	Vector3 normal;
	for (int i = 0; i < 3; ++i)
	{
		normal[2 - i] = c[i] / 255.f * 2.f - 1.f;
	}
	return normal;
}

Vector3 Model::GetVertex(int idx)
{
	return vertices_[idx];
}

Vector3 Model::GetVertex(int face_idx, int vert_idx)
{
	return vertices_[faces_[face_idx][vert_idx][0]];
}

Vector2 Model::GetUV(int face_idx, int vert_idx)
{
	return uvs_[faces_[face_idx][vert_idx][1]];
}

TGAColor Model::GetDiffuse(Vector2 uvf)
{
	Vector2 uv(uvf[0] * diffuse_map.get_width(), uvf[1] * diffuse_map.get_height());
	return diffuse_map.get(uv[0], uv[1]);
}

float Model::GetSpecular(Vector2 uvf)
{
	Vector2 uv(uvf[0] * specular_map.get_width(), uvf[1] * specular_map.get_height());
	return specular_map.get(uv[0], uv[1])[0] * 1.f;
}

std::vector<int> Model::GetFaceVertex(int idx)
{
	std::vector<int> face;
	for (int i = 0; i < (int)faces_[idx].size(); ++i)
	{
		face.push_back(faces_[idx][i][0]);
	}
	return face;
}

void Model::LoadTexture(std::string file_name, const char *suffix, TGAImage &img)
{
	std::string texfile(file_name);
	size_t dot = texfile.find_last_of(".");
	if (dot != std::string::npos) {
		texfile = texfile.substr(0, dot) + std::string(suffix);
		std::cerr << "texture file " << texfile << " loading " << (img.read_tga_file(texfile.c_str()) ? "ok" : "failed") << std::endl;
		img.flip_vertically();
	}
}

void Model::set_position(Vector3 position)
{
	this->position_ = position;
}

void Model::set_scale(Vector3 scale)
{
	this->scale_ = scale;
}

void Model::set_rotate(Vector3 rotate)
{
	this->rotate_ = rotate;
}

Matrix4x4 Model::GetModelMatrix()
{
	Matrix4x4 translate = Matrix4x4::Translate(position_);
	//scale
	Matrix4x4 scale_m = Matrix4x4::Scale(scale_);
	//rotate
	Matrix4x4 rot = Matrix4x4::Rotate(rotate_);

	return translate * rot * scale_m;
}
