#include "ParticleContactSolver.h"
#include "Math.h"

//#define DEBUG_MODE

void ParticleContactSolver::UpdateCollisions(Scene* scene, int iterations)
{
	// On itére l'algorithme plusieurs fois pour plus de précision
	for (int i = 0; i < iterations; i++)
	{
		std::vector<ParticleContact>* contacts = generator.UpdateContacts(scene);

		//génération de la liste publique de contacts (utilisé pour le blob)
		if (i == 0)
		{
			contactsLastFrame.clear();
			for (int j = 0; j < contacts->size(); j++)
			{
				contactsLastFrame.push_back(contacts->at(j));
			}
		}

#ifdef DEBUG_MODE
		std::cout << "Contacts : " << contacts->size() << std::endl;
#endif

		//si il n'y a pas de contacts, on arrête d'itérer
		if (contacts->size() == 0)
			return;

		// On résout tout les contacts
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