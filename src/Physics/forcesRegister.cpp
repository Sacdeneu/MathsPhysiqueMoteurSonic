#include "forcesRegister.h"

ForcesRegister::ForcesRegister()
{

}

void ForcesRegister::AddEntry(Particle* particle, ParticleForceGenerator* generator)
{
	// Pour chaque générateur de force qu'on ajoute, on rajoute également la particle à laquelle elle est 
	// associée pour bien pouvoir appliquer la force dessus
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
	// On itère sur la liste des forces pour retirer tous les générateurs de forces associés à la particule p
	std::vector<ForceEntry>::iterator forcesIterator;
	for (forcesIterator = forces.begin(); forcesIterator != forces.end();)
	{
		if (forcesIterator->particle->id == p->id)
			forcesIterator = forces.erase(forcesIterator);
		else
			++forcesIterator;
	}
}