#ifndef PARTICLEARCHIMEDEGENERATOR_H
#define PARTICLEARCHIMEDEGENERATOR_H

#include "particleForceGenerator.h"

class ParticleArchimedeGenerator : public ParticleForceGenerator
{
public:
	//CONSTRUCTEUR
	ParticleArchimedeGenerator();

	/// <summary>
	/// Mise à jour des forces
	/// </summary>
	/// <param name="particle">Particule affectée</param>
	/// <param name="deltaTime">Temps</param>
	void UpdateForce(Particle* particle, float deltaTime);

	//VARIABLES PRIVEES
private:
	float depthMax;
	float waterHeight;
	float volumeObj;
	float density;
	Vector3D gravity;
};
#endif