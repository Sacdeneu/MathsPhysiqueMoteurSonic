#pragma once

#include "Particle.h"
#include "ParticleContact.h"
#include <vector>

class ParticleLink 
{
public:
	//CONSTRUCTEURS

	ParticleLink() = default;

	/// <param name="A">Première particule à lier</param>
	/// <param name="B">Seconde particule à lier</param>
	/// <param name="sizeLink">Taille du lien</param>
	ParticleLink(Particle* A, Particle* B, float sizeLink);


	virtual ParticleContact* CheckCollision();

	//GETTERS

	inline Particle* GetParticleA() { return particles[0]; }
	inline Particle* GetParticleB() { return particles[1]; }

	//VARIABLES PROTEGEES
protected:
	/// <summary>
	/// Liste de particules liées
	/// </summary>
	Particle* particles[2];
	/// <summary>
	/// Taille du lien
	/// </summary>
	float length;
};