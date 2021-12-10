#pragma once
#include "rigidbody.h"
#include <vector>

#define restitutionFactor 0.4f

class Contact
{
public:
	//CONSTRUCTEURS
	
	/// <summary>
	/// Crée un contact de rigidbodys
	/// </summary>
	Contact();

	/// <summary>
	/// Crée un contact entre deux rigidbodys
	/// </summary>
	/// <param name="a">Premier rigidbody</param>
	/// <param name="b">Second rigidbody</param>
	/// <param name="contactNormal">contactNormal</param>
	/// <param name="interpenetration">Interpenetration</param>
	/// <param name="coefRestitution">Coefficient de restitution</param>
	Contact(Rigidbody* a, Rigidbody* b, Vector3D contactNormal, float interpenetration, Vector3D point);
	~Contact() = default;

	//FONCTIONS

	/// <summary>
	/// Résous les contacts(pénétrations et applique des impulsions)
	/// </summary>
	void Resolve();

	//GETTERS

	inline Vector3D GetNormal() { return normal; }
	inline Vector3D GetPoint() { return point; }
	inline float GetInterpenetration() { return interpenetration; }
	inline Rigidbody* GetRigidbodyA() { return rigidbodyA; }
	inline Rigidbody* GetRigidbodyB() { return rigidbodyB; }

	//VARIABLES PRIVEES
private:
	Rigidbody* rigidbodyA;
	Rigidbody* rigidbodyB;
	Vector3D point;
	Vector3D normal;
	float interpenetration;
};
