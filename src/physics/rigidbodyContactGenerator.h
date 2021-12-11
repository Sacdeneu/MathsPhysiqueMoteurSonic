#pragma once
#include "rigidbody.h"
#include "collisionData.h"
#include "../rendering/scene.h"
#include <vector>
#include "rigidbodyLink.h"
#include "primitive.h"
#include "box.h"
#include "plane.h"

#include "AABB.h"

class RigidbodyContactGenerator
{
public:
	//CONSTRUCTEURS
	RigidbodyContactGenerator() = default;
	~RigidbodyContactGenerator() = default;

	//FONCTIONS

	/// <summary>
	/// Vérification et mise à jour des contacts
	/// </summary>
	/// <param name="scene">Scène sur laquelle on vérifie les contacts</param>
	/// <returns>Liste des collisions</returns>
	std::vector<CollisionData>* UpdateContacts(Scene* scene);

	/// <summary>
	/// Ajoute un lien à la liste des liens générant des collisions
	/// </summary>
	/// <param name="p">Lien à ajouter</param>
	void AddrigidbodyLinks(RigidbodyLink* p);

	/// <summary>
	/// Supprime tous les liens associé à un rigidbody
	/// </summary>
	/// <param name="rigidbodyID">ID du rigidbody</param>
	void RemoveAllLinksFromrigidbody(int rigidbodyID);

	/// <summary>
	/// Suppression de la liste des liens générant des collisions
	/// </summary>
	void RemoveAllrigidbodyLink();

private:
	CollisionData* CheckCollision(Primitive* primitiveA, Primitive* primitiveB);
	CollisionData* CheckCollision(Plane* primitiveA, Box* primitiveB);
	
	/// <summary>
	/// Liste des liens qui génèrent des collisions
	/// </summary>
	std::vector<RigidbodyLink*> rigidbodysLinks;
};
