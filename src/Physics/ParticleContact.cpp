#include "ParticleContact.h"

ParticleContact::ParticleContact()
{
}

ParticleContact::ParticleContact(Particle* a, Particle* b, Vector3D contactNormal, float interpenetration)
{
	this->particles[0] = a;
	this->particles[1] = b;
	this->normal = contactNormal;
	this->interpenetration = interpenetration;
}

void ParticleContact::ResolveInterpenetration()
{
	// Les valeurs pour séparer les deux objets
	//Vector3D deltaA = (B->GetMass() / (A->GetMass() + B->GetMass())) * interpenetration * contactNormal;
	//Vector3D deltaB = -(A->GetMass() / (A->GetMass() + B->GetMass())) * interpenetration * contactNormal;
}
