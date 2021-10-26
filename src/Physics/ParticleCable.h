#pragma once
#include "ParticleLink.h"
#include "ParticleContact.h"
#include "Vector3D.h"
#include <vector>

class ParticleCable : public ParticleLink
{
public:
	//CONSTRUCTEUR

	/// <summary>
	/// Crée un cable
	/// </summary>
	/// <param name="A">Première particule à relier</param>
	/// <param name="B">Seconde particule à relier</param>
	/// <param name="length">Taille max du cable</param>
	ParticleCable(Particle* A, Particle* B, float length);

	//FONCTIONS
	
	/// <summary>
	/// Vérifie s'il y a éloignement entre les deux particules
	/// </summary>
	/// <returns>Retourne un contact si éloignement, retourne NULL sinon</returns>
	ParticleContact* CheckCollision() override;
};