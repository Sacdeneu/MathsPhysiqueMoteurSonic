#pragma once
#include "rigidbody.h"
#include "rigidbodyContactGenerator.h"
#include "../rendering/scene.h"
#include <vector>

class RigidbodyContactSolver
{
public:
	//CONSTRUCTEURS

	RigidbodyContactSolver() = default;
	~RigidbodyContactSolver() = default;

	//FONCTIONS

	/// <summary>
	/// Mise � jour des collisions
	/// </summary>
	/// <param name="scene">Scene sur laquelle on mets � jour les collisions</param>
	/// <param name="iterations">Nombre d'it�rations</param>
	void UpdateCollisions(Scene* scene, int iterations);
	
	//VARIABLES

	/// <summary>
	/// G�n�rateurs de contacts entre rigidbodys
	/// </summary>
	RigidbodyContactGenerator generator;

	/// <summary>
	/// Liste de contacts lors de la derni�re frame 
	/// </summary>
	std::vector<RigidbodyContact> contactsLastFrame;
};
