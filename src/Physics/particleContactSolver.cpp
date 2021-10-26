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

		//si il n'y a pas de contacts, on arrête d'itérer
		if (contacts->size() == 0)
			return;

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