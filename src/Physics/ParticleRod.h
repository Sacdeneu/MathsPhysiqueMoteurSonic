#pragma once
#include "ParticleLink.h"
#include "ParticleContact.h"
#include "Vector3D.h"
#include <vector>

class ParticleRod : public ParticleLink 
{
public:
	//CONSTRUCTEUR

	/// <summary>
	/// Cr�e une tige
	/// </summary>
	/// <param name="A">Premi�re particule � relier</param>
	/// <param name="B">Seconde particule � relier</param>
	/// <param name="length">Taille de la tige</param>
	ParticleRod(Particle*A, Particle*B, float length);

	//FONCTIONS

	/// <summary>
	/// V�rifie si la distance les deux particules est diff�rente de la longueur de la tige
	/// </summary>
	/// <returns>Retourne un contact si distance diff�rente, retourne NULL sinon</returns>
	ParticleContact* CheckCollision() override;
};
