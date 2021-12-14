#include "rigidbodyContactGenerator.h"
#include "Math.h"

RigidbodyContactGenerator::RigidbodyContactGenerator() 
{
	// Initialise l'octree
	octree = Octree(Rect(Vector3D(0, 0, 0), Vector3D(20,10,10)), 4, 4);
}

std::vector<CollisionData>* RigidbodyContactGenerator::UpdateContacts(Scene* scene)
{
	std::vector<CollisionData>* collisions = new std::vector<CollisionData>();
	int rigidbodyCountInNode = scene->GetObjectsCount();

	// On remplit l'octree
	octree.Clear();
	for (size_t i = 0; i < rigidbodyCountInNode; i++)
	{
		octree.Insert(scene->gameObjects[i]);
	}
	
	// On recupere les feuilles
	std::vector<Octree*> collisionsNodes;
	octree.GetAllLeafs(collisionsNodes);

	// pour chaque feuille on parcourt la liste des rigidbody et on ajoute les contacts
	for (size_t n = 0; n < collisionsNodes.size(); n++)
	{
		rigidbodyCountInNode = collisionsNodes[n]->objects.size();

		//pour chaque rigidbody de ce noeud...
		for (size_t i = 0; i < rigidbodyCountInNode; i++)
		{
			Rigidbody* rb = collisionsNodes[n]->objects[i];
			//...pour chaque primitive de ce rigidbody...
			for (size_t j = 0; j < rb->GetPrimitiveCount(); j++)
			{
				Primitive* primitive = rb->GetPrimitive(j);
				//...pour chaque autre rigidbody dans le même noeud...
				for (size_t k = i + 1; k < rigidbodyCountInNode; k++)
				{
					Rigidbody* other = collisionsNodes[n]->objects[k];

					if (rb->GetInvMass() + other->GetInvMass() == 0) //les deux objets sont statiques
						continue;

					//...pour chaque primitive de cet autre rigidbody...
					for (size_t l = 0; l < other->GetPrimitiveCount(); l++)
					{
						Primitive* otherPrimitive = other->GetPrimitive(l);
						//...on verifie les contacts potentiels
						CollisionData* newCollision = CheckCollision(primitive, otherPrimitive);
						if (newCollision != NULL) //si il y a eu une collision
							collisions->push_back(*newCollision);
					}
				}
			}
		}
	}

	return collisions;
}

CollisionData* RigidbodyContactGenerator::CheckCollision(Primitive* primitiveA, Primitive* primitiveB)
{
	if (primitiveA->type == PrimitiveType::plane && primitiveB->type == PrimitiveType::box)
	{
		return CheckCollision((Plane*)primitiveA, (Box*)primitiveB);
	}
	return NULL;
}

Vector3D cubeVertices[8] = {
	Vector3D(.5f,.5f,.5f), Vector3D(-.5f,.5f,.5f), Vector3D(-.5f,-.5f,.5f), Vector3D(.5f,-.5f,.5f),
	Vector3D(.5f,.5f,-.5f), Vector3D(-.5f,.5f,-.5f), Vector3D(-.5f,-.5f,-.5f), Vector3D(.5f,-.5f,-.5f)
};

CollisionData* RigidbodyContactGenerator::CheckCollision(Plane* primitiveA, Box* primitiveB)
{
	CollisionData* collision = new CollisionData();
	float a = primitiveA->normal.x;
	float b = primitiveA->normal.y;
	float c = primitiveA->normal.z;
	float d = primitiveA->offset;

	for (int i = 0; i < 8; i++)
	{
		Vector3D point = primitiveB->GetTransform() * cubeVertices[i];
		float dist = a * point.x + b * point.y + c * point.z - d;
		if (dist <= 0) //collision
		{
			Contact* newContact = new Contact(primitiveA->rigidbody, primitiveB->rigidbody, primitiveA->normal, -dist, point);
			collision->AddContact(newContact);
		}
	}

	if (collision->GetContactCount() != 0)
		return collision;
	
	return NULL;
}

// On enregistre le lien
void RigidbodyContactGenerator::AddrigidbodyLinks(RigidbodyLink* p)
{
	rigidbodysLinks.push_back(p);
}

// On retire tous les liens (tige ou cable) associ�s au rigidbody donn�
void RigidbodyContactGenerator::RemoveAllLinksFromrigidbody(int rigidbodyID)
{
	for (int i = rigidbodysLinks.size() - 1; i >= 0; i--)
	{
		auto link = rigidbodysLinks[i];
		if (link->GetrigidbodyA()->id == rigidbodyID || link->GetrigidbodyB()->id == rigidbodyID)
		{
			rigidbodysLinks.erase(std::remove(rigidbodysLinks.begin(), rigidbodysLinks.end(), rigidbodysLinks[i]), rigidbodysLinks.end());
			delete link;
		}		
	}
}

// On retire tout les liens enregistres
void RigidbodyContactGenerator::RemoveAllrigidbodyLink()
{
	for (int i = rigidbodysLinks.size() - 1; i >= 0; i--)
	{
		auto link = rigidbodysLinks[i];
		rigidbodysLinks.erase(std::remove(rigidbodysLinks.begin(), rigidbodysLinks.end(), rigidbodysLinks[i]), rigidbodysLinks.end());
		delete link;
	}
}
