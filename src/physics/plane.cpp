#include "plane.h"

Plane::Plane() : Primitive()
{
	normal = Vector3D(0, 1, 0);
	offset = 0;
	type = PrimitiveType::plane;
}

Plane::Plane(Vector3D _normal, float _offset) : Primitive()
{
	this->normal = _normal;
	this->offset = _offset;
	type = PrimitiveType::plane;
	UpdateOffsetTRS(normal * offset, Quaternion(normal.x, normal.y, normal.z, 0), Vector3D(1, 1, 1));
}