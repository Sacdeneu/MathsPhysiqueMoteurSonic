#pragma once
#include "rigidbodyLink.h"
#include "rigidbodyContact.h"
#include "../math/Vector3D.h"
#include <vector>

class RigidbodyCable : public RigidbodyLink
{
public:
	//CONSTRUCTEUR

	/// <summary>
	/// Crée un cable
	/// </summary>
	/// <param name="A">Première particule à relier</param>
	/// <param name="B">Seconde particule à relier</param>
	/// <param name="length">Taille max du cable</param>
	RigidbodyCable(Rigidbody* A, Rigidbody* B, float length);

	//FONCTIONS
	
	/// <summary>
	/// Vérifie s'il y a éloignement entre les deux particules
	/// </summary>
	/// <returns>Retourne un contact si éloignement, retourne NULL sinon</returns>
	RigidbodyContact* CheckCollision() override;
};