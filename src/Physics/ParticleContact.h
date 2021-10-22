#pragma once
#include "Vector3D.h"
#include "Particle.h"
#include <vector>

class ParticleContact
{
public:
	ParticleContact();
	ParticleContact(Particle* a, Particle* b, Vector3D contactNormal, float interpenetration);
	~ParticleContact() = default;

	void Resolve();

	inline Vector3D GetNormal() { return normal; }
	inline float GetInterpenetration() { return interpenetration; }

private:
	Particle* particles[2];
	Vector3D normal;
	float interpenetration; 



};
