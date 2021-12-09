#pragma once
#include "rigidbody.h"

class Primitive
{
public:
	//CONSTRUCTEURS
	Primitive();
	~Primitive() = default;

	inline Matrix4 GetTransform() { return body->transformMatrix; }
	inline Rigidbody* GetRigidbody() { return body; }

private:
	Rigidbody* body;
};
