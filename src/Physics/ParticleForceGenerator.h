#ifndef PARTICLEFORCEGENERATOR_H
#define PARTICLEFORCEGENERATOR_H

#include "Particle.h"

class ParticleForceGenerator
{
public:
	virtual void UpdateForce(Particle* particle, float deltaTime) = 0;
};
#endif

