#include "cube.h"
#include <iostream>

std::vector<Vector3> *Cube::vertices()
{
	return &vertices_;
}

std::vector<int> *Cube::triangles()
{
	return &triangles_;
}

std::vector<Vector3> *Cube::normals()
{
	return &normals_;
}

Vector3 Cube::position() const
{
	return position_;
}

void Cube::set_position(Vector3 position)
{
	position_ = position;
}

Vector3 Cube::scale() const
{
	return scale_;
}

void Cube::set_scale(Vector3 scale)
{
	scale_ = scale;
}

Vector3 Cube::rotation() const
{
	return rotation_;
}

void Cube::set_rotation(Vector3 rotation)
{
	rotation_ = rotation;
}

Cube::Cube() : position_(), scale_(), rotation_()
{
}

