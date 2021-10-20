#ifndef PARTICLEANCHOREDSPRINGGENERATOR_H
#define PARTICLEANCHOREDSPRINGGENERATOR_H

#include "particleForceGenerator.h"

class ParticleAnchoredSpringGenerator : public ParticleForceGenerator
{
public:
	//CONSTRUCTEUR
	ParticleAnchoredSpringGenerator();

	/// <summary>
	/// Mise à jour des forces
	/// </summary>
	/// <param name="particle">Particule affectée</param>
	/// <param name="deltaTime">Temps</param>
	void UpdateForce(Particle* particle, float deltaTime);

private:
	Vector3D anchorPoint;
	float k;
	float l0;
};
#endif