#pragma once
#include "../math/Vector3D.h"

class Particle
{
public:
	//CONSTRUCTEURS
	
	/// <summary>
	/// Instancie une particule de position et de v�locit� nulle
	/// </summary>
	Particle();

	/// <summary>
	/// Instancie une particule � une position indiqu�e et de masse sp�cifi�e
	/// </summary>
	/// <param name="initialPos">Position initiale de la particule</param>
	/// <param name="mass">Masse de la particule</param>
	Particle(Vector3D initialPos, float mass);
	//~Particle();

	//FONCTIONS

	/// <summary>
	/// Fonction de mise � jour de position et de v�locit� de la particule
	/// </summary>
	/// <param name="deltaTime">Temps de la simulation</param>
	void Update(float deltaTime);
	
	/// <summary>
	/// Mise � jour de la v�locit� de la particule
	/// </summary>
	/// <param name="newVelocity">Nouvelle v�locit�</param>
	void SetVelocity(Vector3D newVelocity);

	/// <summary>
	/// Mise � jour de la masse de la particule
	/// </summary>
	/// <param name="newMass">Nouvelle masse</param>
	inline void SetMass(float newMass);
	inline float GetInvMass() { return invMass; }
	inline float GetMass() { return 1.0f / invMass; }

	// GETTERS
	Vector3D GetPosition() { return position; }
	inline void SetPosition(Vector3D newPosition) { position = newPosition; }
	inline Vector3D GetVelocity() { return velocity; }
	inline float GetRadius() { return radius; }
	inline void AddForce(Vector3D force) { totalForce = totalForce + force; }
	inline void CleanTotalForce() { totalForce = Vector3D(0, 0, 0); }

	//VARIABLES
protected: 
	/// <summary>
	/// Position de la particule
	/// </summary>
	Vector3D position;

	/// <summary>
	/// V�locit� de la particule
	/// </summary>
	Vector3D velocity;

	/// <summary>
	/// Rayon de la particule
	/// </summary>
	float radius;

	/// <summary>
	/// Inverse de la masse de la particule
	/// </summary>
	float invMass;

public:
	/// <summary>
	/// ID de la particule
	/// </summary>
	int id;

	/// <summary>
	/// Force totale appliqu�e sur la particule
	/// </summary>
	Vector3D totalForce;

	/// <summary>
	/// Bool�en d�finissant si la particule est un blob
	/// </summary>
	bool isBlob;

	/// <summary>
	/// Bool�en d�finissant si la particule poss�de un AABB
	/// </summary>
	bool isAABB;
};

