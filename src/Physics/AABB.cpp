#include "AABB.h"
#include "Math.h"
#include "../math/Vector3D.h"
#include "../rendering/scene.h"

AABB::AABB() : Rigidbody()
{
	invMass = 0;
	isAABB = true;
}

AABB::AABB(Vector3D position, Vector3D scale, int textureID) : Rigidbody()
{
	invMass = 0;
	isAABB = true;
	this->position = position;
	this->scale = scale;
	this->textureID = textureID;
}