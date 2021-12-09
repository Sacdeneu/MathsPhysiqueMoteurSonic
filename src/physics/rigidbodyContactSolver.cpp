#include "rigidbodyContactSolver.h"
#include "Math.h"

//#define DEBUG_MODE

void RigidbodyContactSolver::UpdateCollisions(Scene* scene, int iterations)
{
	// On it�re l'algorithme plusieurs fois pour plus de pr�cisions
	for (int i = 0; i < iterations; i++)
	{
		std::vector<Contact>* contacts = generator.UpdateContacts(scene);

		//g�n�ration de la liste publique de contacts (utilis�e pour le blob)
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

		//S'il n'y a pas de contacts, on arr�te d'it�rer
		if (contacts->size() == 0)
			return;

		// On r�sout tous les contacts
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