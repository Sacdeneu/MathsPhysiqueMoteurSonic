#pragma once
#include "primitive.h"

class Box : public Primitive
{
public:
	//CONSTRUCTEURS
	Box();
	Box(Vector3D _halfSizes);
	Box(Vector3D positionOffset, Vector3D _halfSizes);

public:
	Vector3D halfSizes;
};
