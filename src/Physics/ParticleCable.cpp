#include "ParticleCable.h"

ParticleCable::ParticleCable(Particle* A, Particle* B, float length) : ParticleLink(A, B, length)
{

}

void ParticleCable::AddContacts(std::vector<ParticleContact>* listContacts)
{
	//std::vector<ParticleContact>* res;
	Vector3D vectorDistance = particles[0]->GetPosition() - particles[1]->GetPosition();
	float distance = Vector3D::NormSquare(vectorDistance);

	// Si la distance entre les deux particles est plus grande que la longueur du cable, alors on applique une
	// collision pour faire rapprocher les particules
	if (distance > (length * length))
	{
		listContacts->push_back(ParticleContact(particles[0], particles[1], Vector3D::Normalisation(-vectorDistance), 0, 0));
		listContacts->push_back(ParticleContact(particles[1], particles[0], Vector3D::Normalisation(vectorDistance), 0, 0));
	}
	//return res;

}
