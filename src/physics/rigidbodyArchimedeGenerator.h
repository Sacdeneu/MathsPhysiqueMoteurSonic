#ifndef rigidbodyARCHIMEDEGENERATOR_H
#define rigidbodyARCHIMEDEGENERATOR_H

#include "rigidbodyForceGenerator.h"

class RigidbodyArchimedeGenerator : public RigidbodyForceGenerator
{
public:
	//CONSTRUCTEUR
	RigidbodyArchimedeGenerator();

	/// <summary>
	/// Mise � jour des forces
	/// </summary>
	/// <param name="rigidbody">Particule affect�e</param>
	/// <param name="deltaTime">Temps</param>
	void UpdateForce(Rigidbody* rigidbody, float deltaTime);

	//VARIABLES PRIVEES
private:
	float depthMax;
	float waterHeight;
	float volumeObj;
	float density;
	Vector3D gravity;
};
#endif