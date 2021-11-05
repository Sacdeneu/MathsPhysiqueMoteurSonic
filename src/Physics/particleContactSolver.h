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
	/// Mise � jour des collisions
	/// </summary>
	/// <param name="scene">Scene sur laquelle on mets � jour les collisions</param>
	/// <param name="iterations">Nombre d'it�rations</param>
	void UpdateCollisions(Scene* scene, int iterations);
	
	//VARIABLES

	/// <summary>
	/// G�n�rateurs de contacts entre particules
	/// </summary>
	ParticleContactGenerator generator;

	/// <summary>
	/// Liste de contacts lors de la derni�re frame 
	/// </summary>
	std::vector<ParticleContact> contactsLastFrame;
};
