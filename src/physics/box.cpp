#include "box.h"

Box::Box() : Primitive()
{
	this->halfSizes = Vector3D(0.5f, 0.5f, 0.5f);
	type = PrimitiveType::box;
}

Box::Box(Vector3D _halfSizes) : Primitive()
{
	this->halfSizes = _halfSizes;
	type = PrimitiveType::box;
	UpdateOffsetTRS(Vector3D(0, 0, 0), Quaternion(), this->halfSizes * 2);
}

Box::Box(Vector3D positionOffset, Vector3D _halfSizes) : Primitive()
{
	this->halfSizes = _halfSizes;
	type = PrimitiveType::box;
	UpdateOffsetTRS(positionOffset, Quaternion(), this->halfSizes * 2);
}