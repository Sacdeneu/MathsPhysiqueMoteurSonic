#pragma once
#include "ParticleLink.h"
#include "ParticleContact.h"
#include "Vector3D.h"
#include <vector>

class ParticleCable : public ParticleLink
{
public:
	ParticleCable(Particle* A, Particle* B, float length);
	void AddContacts(std::vector<ParticleContact>* listContacts) override;
};