#pragma once

#include "rigidbody.h"
#include "rigidbodyContact.h"
#include <vector>

class RigidbodyLink 
{
public:
	//CONSTRUCTEURS

	RigidbodyLink() = default;

	/// <param name="A">Premi�re particule � lier</param>
	/// <param name="B">Seconde particule � lier</param>
	/// <param name="sizeLink">Taille du lien</param>
	RigidbodyLink(Rigidbody* A, Rigidbody* B, float sizeLink);


	virtual RigidbodyContact* CheckCollision();

	//GETTERS

	inline Rigidbody* GetrigidbodyA() { return rigidbodys[0]; }
	inline Rigidbody* GetrigidbodyB() { return rigidbodys[1]; }

	//VARIABLES PROTEGEES
protected:
	/// <summary>
	/// Liste de particules li�es
	/// </summary>
	Rigidbody* rigidbodys[2];
	/// <summary>
	/// Taille du lien
	/// </summary>
	float length;
};