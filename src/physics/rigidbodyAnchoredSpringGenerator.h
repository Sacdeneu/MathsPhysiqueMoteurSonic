#ifndef rigidbodyANCHOREDSPRINGGENERATOR_H
#define rigidbodyANCHOREDSPRINGGENERATOR_H

#include "rigidbodyForceGenerator.h"

class RigidbodyAnchoredSpringGenerator : public RigidbodyForceGenerator
{
public:
	//CONSTRUCTEUR
	RigidbodyAnchoredSpringGenerator(Vector3D pos, float length);

	/// <summary>
	/// Mise à jour des forces
	/// </summary>
	/// <param name="rigidbody">Rigidbody affecté</param>
	/// <param name="deltaTime">Temps</param>
	void UpdateForce(Rigidbody* rigidbody, float deltaTime);

	//VARIABLES PRIVEES

private:
	Vector3D anchorPoint;
	float k;
	float l0;
};
#endif