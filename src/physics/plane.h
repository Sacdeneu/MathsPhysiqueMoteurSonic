#pragma once
#include "primitive.h"

class Plane : public Primitive
{
public:
	//CONSTRUCTEURS
	Plane();
	Plane(Vector3D _normal, float _offset);
	~Plane() = default;

public:
	Vector3D normal;
	float offset;
};
