#ifndef rigidbodySPRINGGENERATOR_H
#define rigidbodySPRINGGENERATOR_H

#include "rigidbodyForceGenerator.h"

class RigidbodySpringGenerator : public RigidbodyForceGenerator
{
public:
	//CONSTRUCTEUR
	RigidbodySpringGenerator(Rigidbody* other, float length);

	/// <summary>
	/// Mise � jour des forces
	/// </summary>
	/// <param name="rigidbody">Rigidbody affect�e</param>
	/// <param name="deltaTime">Temps</param>
	void UpdateForce(Rigidbody* rigidbody, float deltaTime);

	//VARIABLES PRIVEES

private:
	Rigidbody* other;
	float k;
	float l0;
};
#endif