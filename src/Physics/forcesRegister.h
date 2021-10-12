#ifndef FORCESREGISTER_H
#define FORCESREGISTER_H

#include "particleForceGenerator.h"
#include <vector>

struct ForceEntry
{
	Particle* particle;
	ParticleForceGenerator* generator;
};

class ForcesRegister
{
public:
	ForcesRegister();
	void AddEntry(Particle* particle, ParticleForceGenerator* generator);
	void DeleteParticle(Particle* p);
	void Update(float deltaTime);
	std::vector<ForceEntry> forces;
};
#endif

