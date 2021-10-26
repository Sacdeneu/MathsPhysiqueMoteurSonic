#pragma once
#include "Vector3D.h"
#include "Particle.h"
#include "ParticleContact.h"
#include "../rendering/scene.h"
#include <vector>
#include "ParticleLink.h"

class ParticleContactGenerator
{
public:
	ParticleContactGenerator() = default;
	~ParticleContactGenerator() = default;

	std::vector<ParticleContact>* UpdateContacts(Scene* scene);
	void AddParticleLink(ParticleLink* p);
	void RemoveAllParticleLink();

private:
	//collision entre deux sph�res
	ParticleContact* CheckCollision(Particle* a, Particle* b);
	//collision entre une sph�re et un AABB
	ParticleContact* CheckCollision(Particle* a, AABB* b);
	
	//liste des liens qui g�n�rent des collisions
	std::vector<ParticleLink*> particlesLinks;
};
