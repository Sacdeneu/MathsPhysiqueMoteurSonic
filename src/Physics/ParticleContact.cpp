#include "ParticleContact.h"

ParticleContact::ParticleContact()
{
}

ParticleContact::ParticleContact(Particle* A, Particle* B, Vector3D contactNormal, float interpenetration)
{
	contacts[0] = A;
	contacts[1] = B;
	this->contactNormal = contactNormal;
	this->interpenetration = interpenetration;




}

void ParticleContact::ResolveInterpenetration()
{
	// Les valeurs pour séparer les deux objets
	//Vector3D deltaA = (B->GetMass() / (A->GetMass() + B->GetMass())) * interpenetration * contactNormal;
	//Vector3D deltaB = -(A->GetMass() / (A->GetMass() + B->GetMass())) * interpenetration * contactNormal;
}
