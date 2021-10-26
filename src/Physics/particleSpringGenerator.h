#ifndef PARTICLESPRINGGENERATOR_H
#define PARTICLESPRINGGENERATOR_H

#include "particleForceGenerator.h"

class ParticleSpringGenerator : public ParticleForceGenerator
{
public:
	//CONSTRUCTEUR
	ParticleSpringGenerator(Particle* other, float length);

	/// <summary>
	/// Mise à jour des forces
	/// </summary>
	/// <param name="particle">Particule affectée</param>
	/// <param name="deltaTime">Temps</param>
	void UpdateForce(Particle* particle, float deltaTime);

	//VARIABLES PRIVEES

private:
	Particle* other;
	float k;
	float l0;
};
#endif