#include "plane.h"

Plane::Plane()
{
	normal = Vector3D(0, 1, 0);
	offset = 0;
}

Plane::Plane(Vector3D _normal, float _offset)
{
	this->normal = _normal;
	this->offset = _offset;
}