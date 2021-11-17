#pragma once
#include "rigidbody.h"
#include <vector>

#define c 0.4f

class RigidbodyContact
{
public:
	//CONSTRUCTEURS
	
	/// <summary>
	/// Crée un contact de particules
	/// </summary>
	RigidbodyContact();

	/// <summary>
	/// Crée un contact entre deux particules
	/// </summary>
	/// <param name="a">Première particule</param>
	/// <param name="b">Seconde particule</param>
	/// <param name="contactNormal">contactNormal</param>
	/// <param name="interpenetration">Interpenetration</param>
	/// <param name="coefRestitution">Coefficient de restitution</param>
	RigidbodyContact(Rigidbody* a, Rigidbody* b, Vector3D contactNormal, float interpenetration, float coefRestitution = c);
	~RigidbodyContact() = default;

	//FONCTIONS

	/// <summary>
	/// Résous les contacts(pénétrations et applique des impulsions)
	/// </summary>
	void Resolve();

	//GETTERS

	inline Vector3D GetNormal() { return normal; }
	inline float GetInterpenetration() { return interpenetration; }
	inline Rigidbody* GetrigidbodyA() { return rigidbodys[0]; }
	inline Rigidbody* GetrigidbodyB() { return rigidbodys[1]; }

	//VARIABLES PRIVEES
private:
	Rigidbody* rigidbodys[2];
	Vector3D normal;
	float interpenetration; 
	float coefRestitution;



};
