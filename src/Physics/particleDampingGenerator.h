#ifndef PARTICLEDAMPINGGENERATOR_H
#define PARTICLEDAMPINGGENERATOR_H

#include "particleForceGenerator.h"

class ParticleDampingGenerator : public ParticleForceGenerator
{
public:
	//CONSTRUCTEUR

	/// <summary>
	/// Initialise un générateur de damping avec k1=0.1 et k2=0.01 (valeurs choisies arbitrairement après tests)
	/// </summary>
	ParticleDampingGenerator();

	/// <summary>
	/// Mise à jour des forces
	/// </summary>
	/// <param name="particle">Particule affectée</param>
	/// <param name="deltaTime">Temps</param>
	void UpdateForce(Particle* particle, float deltaTime);

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