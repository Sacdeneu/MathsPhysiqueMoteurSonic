#pragma once
#include "Particle.h"
#include <vector>
#define c 0.4f
class ParticleContact
{
public:
	//CONSTRUCTEURS
	
	/// <summary>
	/// Cr�e un contact de particules
	/// </summary>
	ParticleContact();

	/// <summary>
	/// Cr�e un contact entre deux particules
	/// </summary>
	/// <param name="a">Premi�re particule</param>
	/// <param name="b">Seconde particule</param>
	/// <param name="contactNormal">contactNormal</param>
	/// <param name="interpenetration">Interpenetration</param>
	/// <param name="coefRestitution">Coefficient de restitution</param>
	ParticleContact(Particle* a, Particle* b, Vector3D contactNormal, float interpenetration, float coefRestitution = c);
	~ParticleContact() = default;

	//FONCTIONS

	/// <summary>
	/// R�sous les contacts(p�n�trations et applique des impulsions)
	/// </summary>
	void Resolve();

	//GETTERS

	inline Vector3D GetNormal() { return normal; }
	inline float GetInterpenetration() { return interpenetration; }
	inline Particle* GetParticleA() { return particles[0]; }
	inline Particle* GetParticleB() { return particles[1]; }

	//VARIABLES PRIVEES
private:
	Particle* particles[2];
	Vector3D normal;
	float interpenetration; 
	float coefRestitution;



};
