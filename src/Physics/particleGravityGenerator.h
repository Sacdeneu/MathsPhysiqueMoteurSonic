#ifndef PARTICLEGRAVITYGENERATOR_H
#define PARTICLEGRAVITYGENERATOR_H

#include "particleForceGenerator.h"

class ParticleGravityGenerator: public ParticleForceGenerator
{
public:
	ParticleGravityGenerator();
	void UpdateForce(Particle* particle, float deltaTime);

private:
	Vector3D gravity;
};
#endif

