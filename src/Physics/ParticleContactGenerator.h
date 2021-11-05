#pragma once
#include "Particle.h"
#include "ParticleContact.h"
#include "../rendering/scene.h"
#include <vector>
#include "ParticleLink.h"

class ParticleContactGenerator
{
public:
	//CONSTRUCTEURS
	ParticleContactGenerator() = default;
	~ParticleContactGenerator() = default;

	//FONCTIONS

	/// <summary>
	/// V�rification et mise � jour des contacts
	/// </summary>
	/// <param name="scene">Sc�ne sur laquelle on v�rifie les contacts</param>
	/// <returns>Liste des collisions</returns>
	std::vector<ParticleContact>* UpdateContacts(Scene* scene);

	/// <summary>
	/// Ajoute un lien � la liste des liens g�n�rant des collisions
	/// </summary>
	/// <param name="p">Lien � ajouter</param>
	void AddParticleLinks(ParticleLink* p);

	/// <summary>
	/// Supprime tous les liens associ� � une particule
	/// </summary>
	/// <param name="particleID">ID de la particule</param>
	void RemoveAllLinksFromParticle(int particleID);

	/// <summary>
	/// Suppression de la liste des liens g�n�rant des collisions
	/// </summary>
	void RemoveAllParticleLink();

private:
	/// <summary>
	/// V�rification de collision entre deux sph�res
	/// </summary>
	/// <param name="a">Premi�re sph�re</param>
	/// <param name="b">Deuxi�me sph�re</param>
	/// <returns>Retourne un contact s'il y a une collision, sinon retourne NULL</returns>
	ParticleContact* CheckCollision(Particle* a, Particle* b);

	/// <summary>
	/// V�rification de collision entre une sph�re et un AABB
	/// </summary>
	/// <param name="a">Sph�re</param>
	/// <param name="b">AABB</param>
	/// <returns>Retourne un contact s'il y a une collision, sinon retourne NULL</returns>
	ParticleContact* CheckCollision(Particle* a, AABB* b);
	
	/// <summary>
	/// Liste des liens qui g�n�rent des collisions
	/// </summary>
	std::vector<ParticleLink*> particlesLinks;
};
