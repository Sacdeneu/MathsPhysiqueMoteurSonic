#include "rigidbodyContactGenerator.h"
#include "Math.h"

std::vector<CollisionData>* RigidbodyContactGenerator::UpdateContacts(Scene* scene)
{
	std::vector<CollisionData>* collisions = new std::vector<CollisionData>();
	int rigidbodyCount = scene->GetObjectsCount();

	//pour chaque rigidbody...
	for (size_t i = 0; i < rigidbodyCount; i++)
	{
		Rigidbody* rb = scene->gameObjects[i];
		//...pour chaque primitive de ce rigidbody...
		for (size_t j = 0; j < rb->GetPrimitiveCount(); j++)
		{
			Primitive* primitive = rb->GetPrimitive(j);
			//...pour chaque autre rigidbody...
			for (size_t k = i + 1; k < rigidbodyCount; k++)
			{
				Rigidbody* other = scene->gameObjects[k];

				if (rb->GetInvMass() + other->GetInvMass() == 0) //les deux objets sont statiques
					continue;

				//...pour chaque primitive de cet autre rigidbody...
				for (size_t l = 0; l < other->GetPrimitiveCount(); l++)
				{
					Primitive* otherPrimitive = other->GetPrimitive(l);
					//...on vérifie les contacts potentiels
					CollisionData* newCollision = CheckCollision(primitive, otherPrimitive);
					if (newCollision != NULL) //si il y a eu une collision
						collisions->push_back(*newCollision);
				}
			}
		}
	}

	// on génère égalment des collisions pour chaque lien
	/*
	for (size_t i = 0; i < rigidbodysLinks.size(); i++)
	{
		Contact* newContact = rigidbodysLinks[i]->CheckCollision();
		if (newContact != NULL) //si il y a eu de collision
			collisions->push_back(*newContact);
	}
	*/

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
			Contact* newContact = new Contact(primitiveA->rigidbody, primitiveB->rigidbody, primitiveA->normal, -dist, cubeVertices[i]);
			collision->AddContact(newContact);
		}
	}

	if (collision->GetContactCount() != 0)
		return collision;
	
	return NULL;
}

/*
Contact* RigidbodyContactGenerator::CheckCollision(Rigidbody* a, Rigidbody* b)
{
	//on détermine la direction et la distance des deux rigidbodys
	float radius = a->GetRadius() + b->GetRadius();
	Vector3D dir = a->GetPosition() - b->GetPosition();
	float distance = std::abs(Vector3D::NormSquare(dir));

	//si elles ne se touchent pas, on ne génère pas de contact
	if (distance > radius)
		return NULL;

	//si elles se touchent on calcule la normale et l'interpenetration...
	Vector3D normal = Vector3D::Normalisation(dir);
	float interpenetration = radius - Vector3D::Norm(dir);

	//...et on génère le contact
	return new Contact(a, b, normal, interpenetration);
}

Contact* RigidbodyContactGenerator::CheckCollision(Rigidbody* a, AABB* b)
{
	//on détermine le point le plus proche du rigidbody compris dans l'AABB
	Vector3D nearestPointInAABB;
	nearestPointInAABB.x = max(b->GetMinX(), min(a->GetPosition().x, b->GetMaxX()));
	nearestPointInAABB.y = max(b->GetMinY(), min(a->GetPosition().y, b->GetMaxY()));
	nearestPointInAABB.z = max(b->GetMinZ(), min(a->GetPosition().z, b->GetMaxZ()));
	
	//on calcule la distance entre ce point et le rigidbody
	float distance = Vector3D::Norm(nearestPointInAABB - a->GetPosition());

	//si distance entre le point et le rigidbody est plus grand que le rayon,
	//alors le rigidbody ne touche pas l'AABB on ne génère pas de contact
	if (distance > a->GetRadius())
		return NULL;

	float interpenetration = a->GetRadius() - distance;

	//si la rigidbody est entièrement dans l'AABB (interpenetration = rayon)
	//alors on met la normale vers le haut pour pousser les rigidbodys coincées à l'interieur de l'AABB
	Vector3D normal = interpenetration == a->GetRadius() ? Vector3D(0, 1, 0) : Vector3D::Normalisation(a->GetPosition() - nearestPointInAABB);

	return new Contact(a, (Rigidbody*)b, normal, interpenetration);
}
*/


// On enregistre le lien
void RigidbodyContactGenerator::AddrigidbodyLinks(RigidbodyLink* p)
{
	rigidbodysLinks.push_back(p);
}

// On retire tous les liens (tige ou cable) associés au rigidbody donné
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

// On retire tout les liens enregistrés
void RigidbodyContactGenerator::RemoveAllrigidbodyLink()
{
	for (int i = rigidbodysLinks.size() - 1; i >= 0; i--)
	{
		auto link = rigidbodysLinks[i];
		rigidbodysLinks.erase(std::remove(rigidbodysLinks.begin(), rigidbodysLinks.end(), rigidbodysLinks[i]), rigidbodysLinks.end());
		delete link;
	}
}
