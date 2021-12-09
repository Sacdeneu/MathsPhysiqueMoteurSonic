#pragma once
#include "rigidbodyLink.h"
#include "contact.h"
#include "../math/Vector3D.h"
#include <vector>

class RigidbodyRod : public RigidbodyLink 
{
public:
	//CONSTRUCTEUR

	/// <summary>
	/// Cr�e une tige
	/// </summary>
	/// <param name="A">Premier rigidbody � relier</param>
	/// <param name="B">Second rigidbody � relier</param>
	/// <param name="length">Taille de la tige</param>
	RigidbodyRod(Rigidbody*A, Rigidbody*B, float length);

	//FONCTIONS

	/// <summary>
	/// V�rifie si la distance entre les deux rigidbodys est diff�rente de la longueur de la tige
	/// </summary>
	/// <returns>Retourne un contact si distance diff�rente, retourne NULL sinon</returns>
	Contact* CheckCollision() override;
};
