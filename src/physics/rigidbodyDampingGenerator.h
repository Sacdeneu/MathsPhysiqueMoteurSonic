#ifndef rigidbodyDAMPINGGENERATOR_H
#define rigidbodyDAMPINGGENERATOR_H

#include "rigidbodyForceGenerator.h"

class RigidbodyDampingGenerator : public RigidbodyForceGenerator
{
public:
	//CONSTRUCTEUR

	/// <summary>
	/// Initialise un générateur de damping avec k1=0.1 et k2=0.01 (valeurs choisies arbitrairement après tests)
	/// </summary>
	RigidbodyDampingGenerator();

	/// <summary>
	/// Mise à jour des forces
	/// </summary>
	/// <param name="rigidbody">Rigidbody affecté</param>
	/// <param name="deltaTime">Temps</param>
	void UpdateForce(Rigidbody* rigidbody, float deltaTime);

private:
	/// <summary>
	/// Gravité
	/// </summary>
	Vector3D gravity;
	/// <summary>
	/// Coefficients de drag 1
	/// </summary>
	float k1;
	/// <summary>
	/// Coefficients de drag 2
	/// </summary>
	float k2;
};
#endif