#include "ParticleCable.h"

ParticleCable::ParticleCable(Particle* A, Particle* B, float length) : ParticleLink(A, B, length)
{
}

ParticleContact* ParticleCable::CheckCollision()
{
	Vector3D vectorDistance = particles[0]->GetPosition() - particles[1]->GetPosition();
	float distance = Vector3D::NormSquare(vectorDistance);

	// Si la distance entre les deux particules est plus grande que la longueur du câble, alors on applique une
	// collision pour faire rapprocher les particules
	if (distance > (length * length))
	{
		return new ParticleContact(particles[0], particles[1], Vector3D::Normalisation(-vectorDistance), 0, 0);
	}

	return NULL;

}
