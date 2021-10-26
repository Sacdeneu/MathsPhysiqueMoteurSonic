#include "particleBungeeGenerator.h"
#include "Vector3D.h"

ParticleBungeeGenerator::ParticleBungeeGenerator(Particle* other, float length)
{
	this->other = other;
	k = 10.0f;
	l0 = length;
}

void ParticleBungeeGenerator::UpdateForce(Particle* particle, float deltaTime)
{
	Vector3D diff = particle->GetPosition() - other->GetPosition();
	float l = Vector3D::Norm(diff);
	Vector3D dir = Vector3D::Normalisation(diff);
	if (l0 < l) {
		particle->AddForce(dir * (k * (l0 - l)));
	}
}