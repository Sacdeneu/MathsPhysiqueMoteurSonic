#pragma once
#include "Vector3D.h"
#include "Particle.h"
#include "ParticleContactGenerator.h"
#include "../rendering/scene.h"
#include <vector>

class ParticleContactSolver
{
public:
	ParticleContactSolver() = default;
	~ParticleContactSolver() = default;

	void UpdateCollisions(Scene* scene, int iterations);
	ParticleContactGenerator generator;

	std::vector<ParticleContact> contactsLastFrame;
};
