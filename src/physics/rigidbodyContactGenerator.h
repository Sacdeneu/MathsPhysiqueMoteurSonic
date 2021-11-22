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
	/// V�rification et mise � jour des contacts
	/// </summary>
	/// <param name="scene">Sc�ne sur laquelle on v�rifie les contacts</param>
	/// <returns>Liste des collisions</returns>
	std::vector<RigidbodyContact>* UpdateContacts(Scene* scene);

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
	/// <summary>
	/// V�rification de collision entre deux sph�res
	/// </summary>
	/// <param name="a">Premi�re sph�re</param>
	/// <param name="b">Deuxi�me sph�re</param>
	/// <returns>Retourne un contact s'il y a une collision, sinon retourne NULL</returns>
	RigidbodyContact* CheckCollision(Rigidbody* a, Rigidbody* b);

	/// <summary>
	/// V�rification de collision entre une sph�re et un AABB
	/// </summary>
	/// <param name="a">Sph�re</param>
	/// <param name="b">AABB</param>
	/// <returns>Retourne un contact s'il y a une collision, sinon retourne NULL</returns>
	RigidbodyContact* CheckCollision(Rigidbody* a, AABB* b);
	
	/// <summary>
	/// Liste des liens qui g�n�rent des collisions
	/// </summary>
	std::vector<RigidbodyLink*> rigidbodysLinks;
};
