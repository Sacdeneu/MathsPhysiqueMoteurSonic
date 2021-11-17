#include "rigidbodyContactGenerator.h"
#include "Math.h"

std::vector<RigidbodyContact>* RigidbodyContactGenerator::UpdateContacts(Scene* scene)
{
	std::vector<RigidbodyContact>* collisions = new std::vector<RigidbodyContact>();
	int rigidbodyCount = scene->GetObjectsCount();
	int aabbCount = scene->map.size();

	//pour chaque particule on vérifie la collision...
	for (size_t i = 0; i < rigidbodyCount; i++)
	{
		//...avec toutes les autres particules pas encore explorées...
		for (size_t j = i + 1; j < rigidbodyCount; j++)
		{
			RigidbodyContact* newContact = CheckCollision(scene->gameObjects[i], scene->gameObjects[j]);
			if (newContact != NULL) //si il y a eu de collision
				collisions->push_back(*newContact);
		}

		//...et avec les AABB qui consistuent le niveau
		for (size_t j = 0; j < aabbCount; j++)
		{
			RigidbodyContact* newContact = CheckCollision(scene->gameObjects[i], &scene->map[j]);
			if (newContact != NULL) //si il y a eu de collision
				collisions->push_back(*newContact);
		}
	}

	// on génère égalment des collisions pour chaque lien
	for (size_t i = 0; i < rigidbodysLinks.size(); i++)
	{
		RigidbodyContact* newContact = rigidbodysLinks[i]->CheckCollision();
		if (newContact != NULL) //si il y a eu de collision
			collisions->push_back(*newContact);
	}

	return collisions;
}

RigidbodyContact* RigidbodyContactGenerator::CheckCollision(Rigidbody* a, Rigidbody* b)
{
	//on détermine le direction et la distance des deux particules
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
	return new RigidbodyContact(a, b, normal, interpenetration);
}

RigidbodyContact* RigidbodyContactGenerator::CheckCollision(Rigidbody* a, AABB* b)
{
	//on détermine le point le plus proche de la particule compris dans l'AABB
	Vector3D nearestPointInAABB;
	nearestPointInAABB.x = max(b->GetMinX(), min(a->GetPosition().x, b->GetMaxX()));
	nearestPointInAABB.y = max(b->GetMinY(), min(a->GetPosition().y, b->GetMaxY()));
	nearestPointInAABB.z = max(b->GetMinZ(), min(a->GetPosition().z, b->GetMaxZ()));
	
	//on calcule la distance entre ce point et la particule
	float distance = Vector3D::Norm(nearestPointInAABB - a->GetPosition());

	//si distance entre le point et la particule est plus grand que le rayon,
	//alors la particule ne touche pas l'AABB on ne génère pas de contact
	if (distance > a->GetRadius())
		return NULL;

	float interpenetration = a->GetRadius() - distance;

	//si la particule est entièrement dans l'AABB (interpenetration = rayon)
	//alors on met la normale vers le haut pour pousser les particules coincées à l'interieur de l'AABB
	Vector3D normal = interpenetration == a->GetRadius() ? Vector3D(0, 1, 0) : Vector3D::Normalisation(a->GetPosition() - nearestPointInAABB);

	return new RigidbodyContact(a, (Rigidbody*)b, normal, interpenetration);
}


// On enregistre le lien
void RigidbodyContactGenerator::AddrigidbodyLinks(RigidbodyLink* p)
{
	rigidbodysLinks.push_back(p);
}

// On retire tout les liens (tige ou cable) associés à la particule donné
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
