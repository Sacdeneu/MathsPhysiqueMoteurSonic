#ifndef PARTICLEGRAVITYGENERATOR_H
#define PARTICLEGRAVITYGENERATOR_H

#include "particleForceGenerator.h"

class ParticleGravityGenerator: public ParticleForceGenerator
{
public:
	//CONSTRUCTEUR

	/// <summary>
	/// Instancie un g�n�rateur de gravit� selon la pesanteur terrestre (9.81 m s -2)
	/// </summary>
	ParticleGravityGenerator();

	//FONCTIONS

	/// <summary>
	/// Applique la force de gravit�
	/// </summary>
	/// <param name="particle">Particule sur laquelle on applique la force</param>
	/// <param name="deltaTime">Temps de la simulation</param>
	void UpdateForce(Particle* particle, float deltaTime);

	//VARIABLES PRIVEES
private:
	/// <summary>
	/// Force de gravit�
	/// </summary>
	Vector3D gravity;
};
#endif

