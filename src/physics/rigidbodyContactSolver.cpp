#include "rigidbodyContactSolver.h"
#include "Math.h"

//#define DEBUG_MODE

void PrintCollisions(std::vector<CollisionData>* collisions)
{
	for (int i = 0; i < collisions->size(); i++)
	{
		CollisionData collision = collisions->at(i);
		std::cout << "[Collision " << i << " entre les rigidbodies " << collision.GetContact(0)->GetRigidbodyA()->id << " et " << collision.GetContact(0)->GetRigidbodyB()->id << ']' << std::endl;
		for (int j = 0; j < collision.GetContactCount(); j++)
		{
			Contact* contact = collision.GetContact(j);
			std::cout << "    [Contact " << j << "] Normal:" << (contact->GetNormal())
				<< "; Interpenetration:" << (contact->GetInterpenetration())
				<< "; Point de contact (local) :" << (contact->GetPoint())
				<< "; Point de contact (monde) :" << (contact->GetRigidbodyB()->transformMatrix * contact->GetPoint()) << std::endl;
		}
	}
}

void RigidbodyContactSolver::UpdateCollisions(Scene* scene, int iterations)
{
	// On itère l'algorithme plusieurs fois pour plus de précisions
	for (int i = 0; i < iterations; i++)
	{
		std::vector<CollisionData>* collisions = generator.UpdateContacts(scene);

#ifdef DEBUG_MODE
		std::cout << "Collisions : " << collisions->size() << std::endl;
#endif

		//S'il n'y a pas de contacts, on arrête d'itérer
		if (collisions->size() == 0)
			return;

		//DEMO PHASE 4
		Scene::mainScene->isPaused = true;
		PrintCollisions(collisions);
		return;

		//Pour chaque collision...
		for (int j = 0; j < collisions->size(); j++)
		{
			//...on résout le contact avec la plus grande interpenetration
			collisions->at(j).GetDeepestContact()->Resolve();

			for (int k = 0; k < collisions->at(j).GetContactCount(); k++)
			{
				//collisions->at(j).GetContact(k)->Resolve();

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

