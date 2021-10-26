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
	/// Cr�e un cable
	/// </summary>
	/// <param name="A">Premi�re particule � relier</param>
	/// <param name="B">Seconde particule � relier</param>
	/// <param name="length">Taille max du cable</param>
	ParticleCable(Particle* A, Particle* B, float length);

	//FONCTIONS
	
	/// <summary>
	/// V�rifie s'il y a �loignement entre les deux particules
	/// </summary>
	/// <returns>Retourne un contact si �loignement, retourne NULL sinon</returns>
	ParticleContact* CheckCollision() override;
};