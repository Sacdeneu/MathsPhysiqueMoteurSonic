#pragma once
#include "rigidbodyLink.h"
#include "rigidbodyContact.h"
#include "../math/Vector3D.h"
#include <vector>

class RigidbodyRod : public RigidbodyLink 
{
public:
	//CONSTRUCTEUR

	/// <summary>
	/// Crée une tige
	/// </summary>
	/// <param name="A">Première particule à relier</param>
	/// <param name="B">Seconde particule à relier</param>
	/// <param name="length">Taille de la tige</param>
	RigidbodyRod(Rigidbody*A, Rigidbody*B, float length);

	//FONCTIONS

	/// <summary>
	/// Vérifie si la distance les deux particules est différente de la longueur de la tige
	/// </summary>
	/// <returns>Retourne un contact si distance différente, retourne NULL sinon</returns>
	RigidbodyContact* CheckCollision() override;
};
