#ifndef rigidbodyBUNGEEGENERATOR_H
#define rigidbodyBUNGEEGENERATOR_H

#include "rigidbodyForceGenerator.h"

class RigidbodyBungeeGenerator : public RigidbodyForceGenerator
{
public:
	//CONSTRUCTEUR
	RigidbodyBungeeGenerator(Rigidbody* other, float length);

	/// <summary>
	/// Mise à jour des forces
	/// </summary>
	/// <param name="rigidbody">Particule affectée</param>
	/// <param name="deltaTime">Temps</param>
	void UpdateForce(Rigidbody* rigidbody, float deltaTime);

	//VARIABLES PRIVEES
private:
	Rigidbody* other;
	float k;
	float l0;
};
#endif