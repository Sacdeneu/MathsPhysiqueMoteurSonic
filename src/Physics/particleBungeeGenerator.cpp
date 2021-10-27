#include "particleBungeeGenerator.h"
#include "Vector3D.h"

ParticleBungeeGenerator::ParticleBungeeGenerator(Particle* other, float length)
{
	this->other = other;
	k = 10.0f; // constante d'élasticité
	l0 = length;
}

void ParticleBungeeGenerator::UpdateForce(Particle* particle, float deltaTime)
{
	// Application de la loi de Hooke entre deux particules
	Vector3D diff = particle->GetPosition() - other->GetPosition();
	float l = Vector3D::Norm(diff);
	Vector3D dir = Vector3D::Normalisation(diff);

	// Applique uniquement la force durant l'extension de l'élastique
	if (l0 < l) 
	{
		// On applique une force proportionnelle à l'étirement des deux objets (l0 - l)
		particle->AddForce(dir * (k * (l0 - l)));
	}
}