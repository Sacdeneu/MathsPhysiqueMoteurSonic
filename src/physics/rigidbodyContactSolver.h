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
	/// Mise à jour des collisions
	/// </summary>
	/// <param name="scene">Scene sur laquelle on mets à jour les collisions</param>
	/// <param name="iterations">Nombre d'itérations</param>
	void UpdateCollisions(Scene* scene, int iterations);
	
	//VARIABLES

	/// <summary>
	/// Générateurs de contacts entre rigidbodys
	/// </summary>
	RigidbodyContactGenerator generator;

	/// <summary>
	/// Liste de contacts lors de la dernière frame 
	/// </summary>
	std::vector<RigidbodyContact> contactsLastFrame;
};
