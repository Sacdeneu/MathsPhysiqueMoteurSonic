#pragma once
#include "ParticleLink.h"
#include "ParticleContact.h"
#include "Vector3D.h"
#include <vector>

class ParticleRod : public ParticleLink 
{
public:
	ParticleRod(Particle*A, Particle*B, float length);
	void AddContacts(std::vector<ParticleContact>* listContact) override;
};
