#include "AABB.h"
#include "Math.h"
#include "Vector3D.h"
#include "../rendering/scene.h"

AABB::AABB() : Particle()
{
	invMass = 0;
}

AABB::AABB(Vector3D position, Vector3D scale) : Particle()
{
	invMass = 0;
	this->position = position;
	this->scale = scale;
}