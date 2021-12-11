#pragma once
#include "rigidbody.h"
#include "collisionData.h"
#include "../rendering/scene.h"
#include <vector>
#include "rigidbodyLink.h"
#include "primitive.h"
#include "box.h"
#include "plane.h"
#include "Octree.h"

#include "AABB.h"

class RigidbodyContactGenerator
{
public:
	//CONSTRUCTEURS
	RigidbodyContactGenerator();
	~RigidbodyContactGenerator() = default;

	//FONCTIONS

	/// <summary>
	/// V�rification et mise � jour des contacts
	/// </summary>
	/// <param name="scene">Sc�ne sur laquelle on v�rifie les contacts</param>
	/// <returns>Liste des collisions</returns>
	std::vector<CollisionData>* UpdateContacts(Scene* scene);

	/// <summary>
	/// Ajoute un lien � la liste des liens g�n�rant des collisions
	/// </summary>
	/// <param name="p">Lien � ajouter</param>
	void AddrigidbodyLinks(RigidbodyLink* p);

	/// <summary>
	/// Supprime tous les liens associ� � un rigidbody
	/// </summary>
	/// <param name="rigidbodyID">ID du rigidbody</param>
	void RemoveAllLinksFromrigidbody(int rigidbodyID);

	/// <summary>
	/// Suppression de la liste des liens g�n�rant des collisions
	/// </summary>
	void RemoveAllrigidbodyLink();

private:
	CollisionData* CheckCollision(Primitive* primitiveA, Primitive* primitiveB);
	CollisionData* CheckCollision(Plane* primitiveA, Box* primitiveB);
	
	/// <summary>
	/// Liste des liens qui g�n�rent des collisions
	/// </summary>
	std::vector<RigidbodyLink*> rigidbodysLinks;

	Octree octree;
};
