#include "particleSpringGenerator.h"
#include "Vector3D.h"

ParticleSpringGenerator::ParticleSpringGenerator(Particle* other)
{
	this->other = other;
	k = 10.0f;
	l0 = 2;
}

void ParticleSpringGenerator::UpdateForce(Particle* particle, float deltaTime)
{
	Vector3D diff = particle->GetPosition() - other->GetPosition();
	float l = Vector3D::Norm(diff);
	Vector3D dir = Vector3D::Normalisation(diff);
	particle->AddForce(dir * (k * (l0 - l)));
}