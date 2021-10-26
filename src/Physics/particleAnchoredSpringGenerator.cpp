#include "particleAnchoredSpringGenerator.h"
#include "Vector3D.h"

ParticleAnchoredSpringGenerator::ParticleAnchoredSpringGenerator(Vector3D pos, float length)
{
	anchorPoint = pos;
	k = 10.0f; // constante d'élasticité
	l0 = length;
}

void ParticleAnchoredSpringGenerator::UpdateForce(Particle* particle, float deltaTime)
{
	// Application de la loi de Hooke entre une particule et point d'ancrage (statique)
	Vector3D diff = particle->GetPosition() - anchorPoint;
	float l = Vector3D::Norm(diff);
	Vector3D dir = Vector3D::Normalisation(diff);

	// On applique une force proportionnelle à l'étirement des deux objets (l0 - l)
	particle->AddForce(dir * (k * (l0 - l)));
}