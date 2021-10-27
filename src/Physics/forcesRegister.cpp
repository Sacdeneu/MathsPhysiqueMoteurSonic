#include "forcesRegister.h"

ForcesRegister::ForcesRegister()
{

}

void ForcesRegister::AddEntry(Particle* particle, ParticleForceGenerator* generator)
{
	// Pour chaque g�n�rateur de force qu'on ajoute, on rajoute �galement la particle � laquelle elle est 
	// associ�e pour bien pouvoir appliquer la force dessus
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
	// On it�re sur la liste des forces pour retirer tous les g�n�rateurs de forces associ�s � la particule p
	std::vector<ForceEntry>::iterator forcesIterator;
	for (forcesIterator = forces.begin(); forcesIterator != forces.end();)
	{
		if (forcesIterator->particle->id == p->id)
			forcesIterator = forces.erase(forcesIterator);
		else
			++forcesIterator;
	}
}