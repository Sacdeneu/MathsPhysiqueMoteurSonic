#include "rigidbodyContactSolver.h"
#include "Math.h"

//#define DEBUG_MODE

//Affiche toutes les informations du vecteur de CollisionData
void PrintCollisions(std::vector<CollisionData>* collisions)
{
	for (int i = 0; i < collisions->size(); i++)
	{
		CollisionData collision = collisions->at(i);
		std::cout << "\n[Collision " << i << " entre les rigidbodies " << collision.GetContact(0)->GetRigidbodyA()->id << " et " << collision.GetContact(0)->GetRigidbodyB()->id << ']' << std::endl;
		for (int j = 0; j < collision.GetContactCount(); j++)
		{
			Contact* contact = collision.GetContact(j);
			std::cout << "  [Contact " << j << "]\n    - Normale : " << (contact->GetNormal())
				<< "\n    - Interpenetration : " << (contact->GetInterpenetration())
				<< "\n    - Point de contact (monde) : " << (contact->GetPoint())
				<< "\n    - Point de contact (local) : " << (contact->GetRigidbodyB()->transformMatrix.Inverse() * contact->GetPoint()) << std::endl;
		}
	}
}

void RigidbodyContactSolver::UpdateCollisions(Scene* scene, int iterations)
{
	// On it�re l'algorithme plusieurs fois pour plus de pr�cisions
	for (int i = 0; i < iterations; i++)
	{
		std::vector<CollisionData>* collisions = generator.UpdateContacts(scene);

#ifdef DEBUG_MODE
		std::cout << "Collisions : " << collisions->size() << std::endl;
#endif

		//S'il n'y a pas de contacts, on arr�te d'it�rer
		if (collisions->size() == 0)
			return;

		//DEMO PHASE 4
		Scene::mainScene->isPaused = true;
		PrintCollisions(collisions);
		return;

		//Pour chaque collision...
		for (int j = 0; j < collisions->size(); j++)
		{
			//...on r�sout le contact avec la plus grande interpenetration
			collisions->at(j).GetDeepestContact()->Resolve();

			for (int k = 0; k < collisions->at(j).GetContactCount(); k++)
			{
				collisions->at(j).GetContact(k)->Resolve();

#ifdef DEBUG_MODE
				std::cout << "    [Collision " << j << "; Contact "<<k<<"] Normal:"
					<< (collisions->at(j).GetContact(k)->GetNormal())
					<< "; Interpenetration:" << (collisions->at(j).GetContact(k)->GetInterpenetration())
					<< " IDs : " << collisions->at(j).GetContact(k)->GetRigidbodyA()->id
					<< " et " << collisions->at(j).GetContact(k)->GetRigidbodyB()->id << std::endl;
#endif
			}
		}
	}
}

