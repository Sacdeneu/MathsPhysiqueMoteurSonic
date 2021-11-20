#pragma once
#include "../math/Vector3D.h"
#include "../math/Quaternion.h"
#include "../math/Matrix3.h"	
#include "../math/Matrix4.h"

class Rigidbody
{
public:
	//CONSTRUCTEURS
	
	/// <summary>
	/// Instancie un rigidbody de position et de v�locit� nulle
	/// </summary>
	Rigidbody();

	/// <summary>
	/// Instancie une rigidbody � une position indiqu�e et de masse sp�cifi�e
	/// </summary>
	/// <param name="initialPos">Position initiale de la rigidbody</param>
	/// <param name="mass">Masse du rigidbody</param>
	Rigidbody(Vector3D initialPos, float mass);
	//~rigidbody();

	//FONCTIONS

	/// <summary>
	/// Fonction de mise � jour de position et de v�locit� du rigibody
	/// </summary>
	/// <param name="deltaTime">Temps de la simulation</param>
	void Update(float deltaTime);
	
	/// <summary>
	/// Mise � jour de la v�locit� du rigidbody
	/// </summary>
	/// <param name="newVelocity">Nouvelle v�locit�</param>
	void SetVelocity(Vector3D newVelocity);

	/// <summary>
	/// Ajout de force sur un point donn� d'un rigidbody (dans le rep�re du monde)
	/// </summary>
	/// <param name="force">Force � appliquer</param>
	/// <param name="point">Point sur lequel appliquer la force</param>
	void AddForceAtPoint(Vector3D force, Vector3D point);


	/// <summary>
	/// Ajout de force sur un point donn� d'un rigidbody (dans le rep�re de l'objet)
	/// </summary>
	/// <param name="force">Force � appliquer</param>
	/// <param name="point">Point sur lequel appliquer la force</param>
	void AddForceAtBodyPoint(Vector3D force, Vector3D point);

	/// <summary>
	/// Calcul les donn�es d�riv�es du rigidbody
	/// </summary>
	void CalculDerivedData();

	/// <summary>
	/// Mise � jour de la masse du rigidbody
	/// </summary>
	/// <param name="newMass">Nouvelle masse</param>
	inline void SetMass(float newMass);
	inline float GetInvMass() { return invMass; }
	inline float GetMass() { return 1.0f / invMass; }


	// GETTERS + SETTERS
	Vector3D GetPosition() { return position; }
	inline void SetPosition(Vector3D newPosition) { position = newPosition; }
	inline Vector3D GetVelocity() { return velocity; }
	inline float GetRadius() { return radius; }
	inline void AddForce(Vector3D force) { totalForce = totalForce + force; }
	inline void CleanTotalForce() { totalForce = Vector3D(0, 0, 0); }
	inline void CleanTotalTorque() { totalTorque = Vector3D(0, 0, 0); }

	//VARIABLES
protected: 
	/// <summary>
	/// Position du rigidbody
	/// </summary>
	Vector3D position;

	/// <summary>
	/// V�locit� du rigidbody
	/// </summary>
	Vector3D velocity;

	/// <summary>
	/// Vitesse angulaire
	/// </summary>
	Vector3D angularVelocity;
	Quaternion orientation;

	/// <summary>
	/// Accumulateur de couple
	/// </summary>
	Vector3D totalTorque;

	/// <summary>
	/// Matrice inverse du tenseur d'intertie (relative � l'espace objet)
	/// </summary>
	Matrix3 inverseInertiaTensor;

	/// <summary>
	/// Matrice inverse du tenseur d'intertie (relative � l'espace monde)
	/// </summary>
	Matrix3 inverseInertiaTensorWorld;

	/// <summary>
	/// Rayon du rigidbody
	/// </summary>
	float radius;

	/// <summary>
	/// Inverse de la masse du rigidbody
	/// </summary>
	float invMass;

public:
	/// <summary>
	/// ID du rigidbody
	/// </summary>
	int id;

	/// <summary>
	/// Force totale appliqu�e sur le rigidbody
	/// </summary>
	Vector3D totalForce;

	/// <summary>
	/// Bool�en d�finissant si le rigidbody est un blob
	/// </summary>
	bool isBlob;

	/// <summary>
	/// Bool�en d�finissant si le rigidbody poss�de un AABB
	/// </summary>
	bool isAABB;

	Matrix4 transformMatrix;
};

