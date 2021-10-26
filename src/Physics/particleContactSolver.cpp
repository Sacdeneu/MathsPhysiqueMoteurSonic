#include "ParticleContactSolver.h"
#include "Math.h"

//#define DEBUG_MODE

void ParticleContactSolver::UpdateCollisions(Scene* scene, int iterations)
{
	for (int i = 0; i < iterations; i++)
	{
		std::vector<ParticleContact>* contacts = generator.UpdateContacts(scene);

#ifdef DEBUG_MODE
		std::cout << "Contacts : " << contacts->size() << std::endl;
#endif

		if (contacts->size() == 0)
			return;

		// On regarde si les liens de particules génèrent des collisions supplémentaires
		for (size_t i = 0; i < particlesLink.size(); i++)
		{
			particlesLink[i]->AddContacts(contacts);
		}

		for (int j = 0; j < contacts->size(); j++)
		{
			contacts->at(j).Resolve();

#ifdef DEBUG_MODE
			std::cout << "    [" << j << "] Normal:" << (contacts->at(j).GetNormal())
				<< "; Interpenetration:" << (contacts->at(j).GetInterpenetration()) << std::endl;
#endif
		}
	}
}

// à bouger dans scene.cpp si c'est plus cohérent niveau architecture
void ParticleContactSolver::AddParticleLink(ParticleLink* p)
{
	particlesLink.push_back(p);
}
void ParticleContactSolver::RemoveAllParticleLink()
{
	for (int i = particlesLink.size() - 1; i >= 0; i--)
	{
		auto p = particlesLink[i];
		particlesLink.erase(std::remove(particlesLink.begin(), particlesLink.end(), particlesLink[i]), particlesLink.end());
		delete p;
	}
}
