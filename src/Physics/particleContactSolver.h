#pragma once
#include "Particle.h"
#include "ParticleContactGenerator.h"
#include "../rendering/scene.h"
#include <vector>

class ParticleContactSolver
{
public:
	//CONSTRUCTEURS

	ParticleContactSolver() = default;
	~ParticleContactSolver() = default;

	//FONCTIONS

	/// <summary>
	/// Mise à jour des collisions
	/// </summary>
	/// <param name="scene">Scene sur laquelle on mets à jour les collisions</param>
	/// <param name="iterations">Nombre d'itérations</param>
	void UpdateCollisions(Scene* scene, int iterations);
	
	//VARIABLES

	/// <summary>
	/// Générateurs de contacts entre particules
	/// </summary>
	ParticleContactGenerator generator;

	/// <summary>
	/// Liste de contacts lors de la dernière frame 
	/// </summary>
	std::vector<ParticleContact> contactsLastFrame;
};
