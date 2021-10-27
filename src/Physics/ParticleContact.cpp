#include "ParticleContact.h"



ParticleContact::ParticleContact()
{
}

ParticleContact::ParticleContact(Particle* a, Particle* b, Vector3D contactNormal, float interpenetration, float coefRestitution)
{
	this->particles[0] = a;
	this->particles[1] = b;
	this->normal = contactNormal;
	this->interpenetration = interpenetration;
	this->coefRestitution = coefRestitution;
}

// Méthode pour résoudre la collision
void ParticleContact::Resolve()
{
	// On calcule la vitesse d'approche des deux objets
	float totalMass = particles[0]->GetInvMass() + particles[1]->GetInvMass();
	float separationVelocity = Vector3D::ScalarProduct(particles[0]->GetVelocity() - particles[1]->GetVelocity(), this->normal);
	// Si la vitesse d'approche est inférieure à zéro cela veut dire que les particules s'éloignent entre elles, 
	// donc on a déjà le comportement souhaité
	if (separationVelocity > 0) 
		return;
	
	// Sinon on calcule la vitesse de séparation pour justement les éloigner
	float separationVelocity2 = -coefRestitution * separationVelocity;
	float deltaSeparationVelocity = separationVelocity2 - separationVelocity;

	// On applique une impulsion sur les deux particules
	Vector3D impulsion = this->normal * (deltaSeparationVelocity / totalMass);

	particles[0]->SetVelocity(particles[0]->GetVelocity() + impulsion * particles[0]->GetInvMass());
	particles[1]->SetVelocity(particles[1]->GetVelocity() - impulsion * particles[1]->GetInvMass());
		
	// On résout également l'interpénétration en touchant directement aux positions des particules.
	Vector3D correction = this->normal * (this->interpenetration / (particles[0]->GetInvMass() + particles[1]->GetInvMass()));
	particles[0]->SetPosition(particles[0]->GetPosition() + correction * particles[0]->GetInvMass());
	particles[1]->SetPosition(particles[1]->GetPosition() - correction * particles[1]->GetInvMass());
}
  