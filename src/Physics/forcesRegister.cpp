#include "forcesRegister.h"

ForcesRegister::ForcesRegister()
{

}

void ForcesRegister::AddEntry(Particle* particle, ParticleForceGenerator* generator)
{
	ForceEntry newEntry;
	newEntry.particle = particle;
	newEntry.generator = generator;
	forces.push_back(newEntry);
}

void ForcesRegister::Update(float deltaTime)
{
	for (ForceEntry force : forces)
	{
		force.generator->UpdateForce(force.particle, deltaTime);
	}
}

void ForcesRegister::DeleteParticle(Particle* p)
{
	std::vector<ForceEntry>::iterator forcesIterator;
	for (forcesIterator = forces.begin(); forcesIterator != forces.end();)
	{
		if (forcesIterator->particle->id == p->id)
			forcesIterator = forces.erase(forcesIterator);
		else
			++forcesIterator;
	}
}