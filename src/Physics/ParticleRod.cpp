#include "ParticleRod.h"

ParticleRod::ParticleRod(Particle* A, Particle* B, float length)
{
	__super::ParticleLink(A, B, length);
}

std::vector<ParticleContact> ParticleRod::AddContacts()
{
	std::vector<ParticleContact> res;
	Vector3D vectorDistance = particles[0]->GetPosition() - particles[1]->GetPosition();
	float distance = Vector3D::NormSquare(vectorDistance);
	if (distance != (length * length))
	{
		float distanceToRod = distance - length;
		ParticleContact c;
		res.push_back(ParticleContact(particles[0], particles[1], Vector3D::Normalisation(-vectorDistance), distanceToRod));
		res.push_back(ParticleContact(particles[1], particles[0], Vector3D::Normalisation(vectorDistance), distanceToRod));
	}
	return res;

}
