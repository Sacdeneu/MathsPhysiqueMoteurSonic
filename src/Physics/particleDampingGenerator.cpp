#include "particleDampingGenerator.h"
#include "Vector3D.h"

ParticleDampingGenerator::ParticleDampingGenerator()
{
	k1 = 0.98f;
	k2 = 0.02f;
}

void ParticleDampingGenerator::UpdateForce(Particle* particle, float deltaTime)
{
	Vector3D velocity = particle->GetVelocity();
	particle->AddForce(-velocity.Normalisation()*(k1*Vector3D::Norm(velocity)+k2*Vector3D::NormSquare(velocity)));
}
