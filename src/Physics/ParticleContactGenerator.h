#pragma once
#include "Vector3D.h"
#include "Particle.h"
#include "ParticleContact.h"
#include "../rendering/scene.h"
#include <vector>

class ParticleContactGenerator
{
public:
	ParticleContactGenerator() = default;
	~ParticleContactGenerator() = default;

	std::vector<ParticleContact>* UpdateContacts(Scene* scene);

private:
	//collision entre deux sph�res
	ParticleContact* CheckCollision(Particle* a, Particle* b);
	//collision entre une sph�re et un AABB
	ParticleContact* CheckCollision(Particle* a, AABB* b);
};
