#include "Vector3D.h"
#include "particleGravityGenerator.h"

#define GRAVITY -9.81f

ParticleGravityGenerator::ParticleGravityGenerator()
{
	gravity = Vector3D(0, GRAVITY, 0);
}

void ParticleGravityGenerator::UpdateForce(Particle* particle, float deltaTime)
{
	// On applique simplement la gravité sur la particule en fonction de sa masse
	particle->AddForce(gravity * particle->GetMass());
}