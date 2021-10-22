#include "ParticleContact.h"

#define c 0.4f

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

void ParticleContact::Resolve()
{
	float totalMass = particles[0]->GetInvMass() + particles[1]->GetInvMass();
	float separationVelocity = Vector3D::ScalarProduct(particles[0]->GetVelocity() - particles[1]->GetVelocity(), this->normal);
	if (separationVelocity > 0)
		return;
	
	float separationVelocity2 = -c * separationVelocity;
	float deltaSeparationVelocity = separationVelocity2 - separationVelocity;
	Vector3D impulsion = this->normal * (deltaSeparationVelocity / totalMass);

	particles[0]->SetVelocity(particles[0]->GetVelocity() + impulsion * particles[0]->GetInvMass());
	particles[1]->SetVelocity(particles[1]->GetVelocity() - impulsion * particles[1]->GetInvMass());
		
	Vector3D correction = this->normal * (this->interpenetration / (particles[0]->GetInvMass() + particles[1]->GetInvMass()));
	particles[0]->SetPosition(particles[0]->GetPosition() + correction * particles[0]->GetInvMass());
	particles[1]->SetPosition(particles[1]->GetPosition() - correction * particles[1]->GetInvMass());
}
  