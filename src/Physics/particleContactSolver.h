#pragma once
#include "Vector3D.h"
#include "Particle.h"
#include "ParticleContactGenerator.h"
#include "ParticleLink.h"
#include "../rendering/scene.h"
#include <vector>

class ParticleContactSolver
{
public:
	ParticleContactSolver() = default;
	~ParticleContactSolver() = default;

	void UpdateCollisions(Scene* scene, int iterations);
	void AddParticleLink(ParticleLink* p);

private:
	std::vector<ParticleLink*> particlesLink;
	ParticleContactGenerator generator;
};
