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
	/// Cr�e un cable
	/// </summary>
	/// <param name="A">Premier rigidbody � relier</param>
	/// <param name="B">Second rigidbody � relier</param>
	/// <param name="length">Taille max du cable</param>
	RigidbodyCable(Rigidbody* A, Rigidbody* B, float length);

	//FONCTIONS
	
	/// <summary>
	/// V�rifie s'il y a �loignement entre les deux rigidbodys
	/// </summary>
	/// <returns>Retourne un contact si �loignement, retourne NULL sinon</returns>
	RigidbodyContact* CheckCollision() override;
};