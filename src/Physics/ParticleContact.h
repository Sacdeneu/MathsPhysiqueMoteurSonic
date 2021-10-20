#pragma once
#include "Vector3D.h"
#include "Particle.h"
#include <vector>

class ParticleContact
{
public:
	ParticleContact();
	ParticleContact(Particle* A, Particle* B, Vector3D contactNormal, float interpenetration);
	~ParticleContact() = default;

	// Pour r�soudre la superposition des deux particules
	void ResolveInterpenetration();

private:
	Particle* contacts[2];
	float coef;
	Vector3D contactNormal;

	// utilis� pour calculer les distance a laquelle les 2 particules 
	// doivent bouger pour r�soudre la collision
	float interpenetration; 



};
