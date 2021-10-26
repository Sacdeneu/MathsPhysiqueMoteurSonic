#include "particleAnchoredSpringGenerator.h"
#include "Vector3D.h"

ParticleAnchoredSpringGenerator::ParticleAnchoredSpringGenerator(Vector3D pos, float length)
{
	anchorPoint = pos;
	k = 10.0f;
	l0 = length;
}

void ParticleAnchoredSpringGenerator::UpdateForce(Particle* particle, float deltaTime)
{
	Vector3D diff = particle->GetPosition() - anchorPoint;
	float l = Vector3D::Norm(diff);
	Vector3D dir = Vector3D::Normalisation(diff);
	particle->AddForce(dir * (k * (l0 - l)));
}