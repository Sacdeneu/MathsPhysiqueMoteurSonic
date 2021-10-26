#pragma once
#include "ParticleLink.h"
#include "ParticleContact.h"
#include "Vector3D.h"
#include <vector>

class ParticleCable : public ParticleLink
{
public:
	ParticleCable(Particle* A, Particle* B, float length);
	ParticleContact* CheckCollision() override;
};