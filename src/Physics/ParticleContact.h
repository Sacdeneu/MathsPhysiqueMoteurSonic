#pragma once
#include "Vector3D.h"
#include "Particle.h"
#include <vector>
#define c 0.4f
class ParticleContact
{
public:
	ParticleContact();
	ParticleContact(Particle* a, Particle* b, Vector3D contactNormal, float interpenetration, float coefRestitution = c);
	~ParticleContact() = default;

	void Resolve();

	inline Vector3D GetNormal() { return normal; }
	inline float GetInterpenetration() { return interpenetration; }
	inline Particle* GetParticleA() { return particles[0]; }
	inline Particle* GetParticleB() { return particles[1]; }

private:
	Particle* particles[2];
	Vector3D normal;
	float interpenetration; 
	float coefRestitution;



};
