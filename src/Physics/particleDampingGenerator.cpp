#include "particleDampingGenerator.h"
#include "Vector3D.h"

ParticleDampingGenerator::ParticleDampingGenerator()
{
	// Valeurs arbitraire qui rendent bien à l'écran
	k1 = 0.1f;
	k2 = 0.01f;
}

void ParticleDampingGenerator::UpdateForce(Particle* particle, float deltaTime)
{
	Vector3D velocity = particle->GetVelocity();
	particle->AddForce(-velocity.Normalisation()*(k1*Vector3D::Norm(velocity)+k2*Vector3D::NormSquare(velocity)));
}
