#include "ParticleRod.h"

ParticleRod::ParticleRod(Particle* A, Particle* B, float length) : ParticleLink(A, B, length)
{

}
void ParticleRod::AddContacts(std::vector<ParticleContact>* listContact)
{
	//std::vector<ParticleContact>* res = new std::vector<ParticleContact>();
	Vector3D vectorDistance = particles[0]->GetPosition() - particles[1]->GetPosition();
	float distance = Vector3D::NormSquare(vectorDistance);

	// Si la distance entre les deux particles est différente de la longueur du cable, alors on applique soit
	// une collsion pour que les deux particules se rejoignent, soit pour qu'elle s'éloigne
	if (distance > (length * length))
	{
		listContact->push_back(ParticleContact(particles[0], particles[1], Vector3D::Normalisation(-vectorDistance), 0, 0));
		listContact->push_back(ParticleContact(particles[1], particles[0], Vector3D::Normalisation(vectorDistance), 0, 0));
	}
	else  
	{
		listContact->push_back(ParticleContact(particles[0], particles[1], Vector3D::Normalisation(vectorDistance), 0, 0));
		listContact->push_back(ParticleContact(particles[1], particles[0], Vector3D::Normalisation(-vectorDistance), 0, 0));
	}
	//return res;

}
