#pragma once
#include "primitive.h"

class Box : Primitive
{
public:
	//CONSTRUCTEURS
	Box();
	Box(Vector3D _halfSizes);

public:
	Vector3D halfSizes;
};
