#include "particleSpringGenerator.h"

ParticleSpringGenerator::ParticleSpringGenerator(Particle* other, float length)
{
	this->other = other;
	k = 10.0f; // constante d'�lasticit�
	l0 = length;
}

void ParticleSpringGenerator::UpdateForce(Particle* particle, float deltaTime)
{
	// Application de la loi de Hooke entre deux particules
	Vector3D diff = particle->GetPosition() - other->GetPosition();
	float l = Vector3D::Norm(diff);
	Vector3D dir = Vector3D::Normalisation(diff);

	// On applique une force proportionnelle � l'�tirement des deux objets (l0 - l)
	particle->AddForce(dir * (k * (l0 - l)));
}