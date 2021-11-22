#ifndef rigidbodyGRAVITYGENERATOR_H
#define rigidbodyGRAVITYGENERATOR_H

#include "rigidbodyForceGenerator.h"

class RigidbodyGravityGenerator: public RigidbodyForceGenerator
{
public:
	//CONSTRUCTEUR

	/// <summary>
	/// Instancie un générateur de gravité selon la pesanteur terrestre (9.81 m s -2)
	/// </summary>
	RigidbodyGravityGenerator();

	//FONCTIONS

	/// <summary>
	/// Applique la force de gravité
	/// </summary>
	/// <param name="rigidbody">Rigidbody sur lequel on applique la force</param>
	/// <param name="deltaTime">Temps de la simulation</param>
	void UpdateForce(Rigidbody* rigidbody, float deltaTime);

	//VARIABLES PRIVEES
private:
	/// <summary>
	/// Force de gravité
	/// </summary>
	Vector3D gravity;
};
#endif

