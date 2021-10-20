#pragma once
#include "Vector3D.h"
#include "Particle.h"
#include <vector>

class ParticleContact
{
public:
	ParticleContact();
	ParticleContact(Particle* A, Particle* B, Vector3D normal, float interpenetration);
	~ParticleContact() = default;

private:
	Particle* contacts;
	float coef;
	Vector3D contactNormal;

	// utilis� pour calculer les distance a laquelle les 2 particules 
	// doivent bouger pour r�soudre la collision
	float interpenetration; 


};
