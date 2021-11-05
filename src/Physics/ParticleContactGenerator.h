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
	/// Vérification et mise à jour des contacts
	/// </summary>
	/// <param name="scene">Scène sur laquelle on vérifie les contacts</param>
	/// <returns>Liste des collisions</returns>
	std::vector<ParticleContact>* UpdateContacts(Scene* scene);

	/// <summary>
	/// Ajoute un lien à la liste des liens générant des collisions
	/// </summary>
	/// <param name="p">Lien à ajouter</param>
	void AddParticleLinks(ParticleLink* p);

	/// <summary>
	/// Supprime tous les liens associé à une particule
	/// </summary>
	/// <param name="particleID">ID de la particule</param>
	void RemoveAllLinksFromParticle(int particleID);

	/// <summary>
	/// Suppression de la liste des liens générant des collisions
	/// </summary>
	void RemoveAllParticleLink();

private:
	/// <summary>
	/// Vérification de collision entre deux sphères
	/// </summary>
	/// <param name="a">Première sphère</param>
	/// <param name="b">Deuxième sphère</param>
	/// <returns>Retourne un contact s'il y a une collision, sinon retourne NULL</returns>
	ParticleContact* CheckCollision(Particle* a, Particle* b);

	/// <summary>
	/// Vérification de collision entre une sphère et un AABB
	/// </summary>
	/// <param name="a">Sphère</param>
	/// <param name="b">AABB</param>
	/// <returns>Retourne un contact s'il y a une collision, sinon retourne NULL</returns>
	ParticleContact* CheckCollision(Particle* a, AABB* b);
	
	/// <summary>
	/// Liste des liens qui génèrent des collisions
	/// </summary>
	std::vector<ParticleLink*> particlesLinks;
};
