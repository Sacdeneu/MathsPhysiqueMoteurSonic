#include "box.h"

Box::Box()
{
	this->halfSizes = Vector3D(0.5f, 0.5f, 0.5f);
}

Box::Box(Vector3D _halfSizes)
{
	this->halfSizes = _halfSizes;
}