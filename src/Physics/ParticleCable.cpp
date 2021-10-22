#include "ParticleCable.h"

ParticleCable::ParticleCable(Particle* A, Particle* B, float length)
{
	__super::ParticleLink(A, B, length);
}


std::vector<ParticleContact> ParticleCable::AddContacts()
{
	std::vector<ParticleContact> res;
	Vector3D vectorDistance = particles[0]->GetPosition() - particles[1]->GetPosition();
	float distance = Vector3D::NormSquare(vectorDistance);
	if (distance > (length * length))
	{
		res.push_back(ParticleContact(particles[0], particles[1], Vector3D::Normalisation(-vectorDistance), 0));
		res.push_back(ParticleContact(particles[1], particles[0], Vector3D::Normalisation(vectorDistance), 0));
	}
	return res;

}
