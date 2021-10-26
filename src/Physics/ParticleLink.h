#pragma once

#include "Particle.h"
#include "ParticleContact.h"
#include <vector>

class ParticleLink 
{
public:
	ParticleLink() = default;
	ParticleLink(Particle* A, Particle* B, float sizeLink);
	virtual ParticleContact* CheckCollision();


protected:
	Particle* particles[2];
	float length;
};