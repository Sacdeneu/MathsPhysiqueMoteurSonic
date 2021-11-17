#include "forcesRegister.h"

ForcesRegister::ForcesRegister()
{

}

void ForcesRegister::AddEntry(Rigidbody* rigidbody, RigidbodyForceGenerator* generator)
{
	// Pour chaque g�n�rateur de force qu'on ajoute, on rajoute �galement la rigidbody � laquelle elle est 
	// associ�e pour bien pouvoir appliquer la force dessus
	ForceEntry newEntry;
	newEntry.rigidbody = rigidbody;
	newEntry.generator = generator;
	forces.push_back(newEntry);
}

void ForcesRegister::Update(float deltaTime)
{
	for (ForceEntry force : forces)
	{
		force.generator->UpdateForce(force.rigidbody, deltaTime);
	}
}

void ForcesRegister::Deleterigidbody(Rigidbody* p)
{
	// On it�re sur la liste des forces pour retirer tous les g�n�rateurs de forces associ�s � la particule p
	std::vector<ForceEntry>::iterator forcesIterator;
	for (forcesIterator = forces.begin(); forcesIterator != forces.end();)
	{
		if (forcesIterator->rigidbody->id == p->id)
			forcesIterator = forces.erase(forcesIterator);
		else
			++forcesIterator;
	}
}