#pragma once
#include "rigidbody.h"
#include "rigidbodyContact.h"
#include "../rendering/scene.h"
#include <vector>
#include "rigidbodyLink.h"

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
	std::vector<RigidbodyContact>* UpdateContacts(Scene* scene);

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
	/// <summary>
	/// Vérification de collision entre deux sphères
	/// </summary>
	/// <param name="a">Première sphère</param>
	/// <param name="b">Deuxième sphère</param>
	/// <returns>Retourne un contact s'il y a une collision, sinon retourne NULL</returns>
	RigidbodyContact* CheckCollision(Rigidbody* a, Rigidbody* b);

	/// <summary>
	/// Vérification de collision entre une sphère et un AABB
	/// </summary>
	/// <param name="a">Sphère</param>
	/// <param name="b">AABB</param>
	/// <returns>Retourne un contact s'il y a une collision, sinon retourne NULL</returns>
	RigidbodyContact* CheckCollision(Rigidbody* a, AABB* b);
	
	/// <summary>
	/// Liste des liens qui génèrent des collisions
	/// </summary>
	std::vector<RigidbodyLink*> rigidbodysLinks;
};
