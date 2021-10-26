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
	/// Crée une tige
	/// </summary>
	/// <param name="A">Première particule à relier</param>
	/// <param name="B">Seconde particule à relier</param>
	/// <param name="length">Taille de la tige</param>
	ParticleRod(Particle*A, Particle*B, float length);

	//FONCTIONS

	/// <summary>
	/// Vérifie si la distance les deux particules est différente de la longueur de la tige
	/// </summary>
	/// <returns>Retourne un contact si distance différente, retourne NULL sinon</returns>
	ParticleContact* CheckCollision() override;
};
