#pragma once
#include <iostream>
#include "Vector3D.h"

class Quaternion
{
public:

	//CONSTRUCTEURS

	/// <summary>
	/// Initialiser un quaternion � (0, 0, 0, 1)
	/// </summary>
	Quaternion();

	/// <summary>
	/// Initialiser un quaternion pour les valeurs donn�es
	/// </summary>
	/// <param name="x">Valeur de l'axe X</param>
	/// <param name="y">Valeur de l'axe Y</param>
	/// <param name="z">Valeur de l'axe Z</param>
	/// <param name="w">Quantit� de rotation sur les axes</param>
	Quaternion(float x, float y, float z, float w);

	Quaternion(const Quaternion&) = default;


	// SURCHARGES D'OPERATEURS

	Quaternion operator*(const float&);
	Quaternion operator+(const Quaternion&);
	Quaternion operator-(const Quaternion&);
	Quaternion operator*(const Quaternion&);
	Vector3D operator*(const Vector3D&);
	float& operator[](size_t index);
	const float& operator[](size_t index) const;
	friend std::ostream& operator<<(std::ostream& os, Quaternion mat);

	//FONCTIONS

	/// <summary>
	/// Normalisation du quaternion actuel
	/// </summary>
	void Normalize();

	/// <summary>
	/// Normale un quaternion
	/// </summary>
	/// <param name="">Quaternion � normaliser</param>
	/// <returns>Quaternion normalis�</returns>
	Quaternion Normalize(Quaternion);

	void RotateByVector();

	/// <summary>
	/// Fonction de mise � jour de la vitesse angulaire
	/// </summary>
	/// <param name="angularVelocity">Quaternion de vitesse angulaire � mettre � jour</param>
	/// <param name="deltaTime">Temps de la simulation</param>
	void UpdateAngularVelocity(Quaternion angularVelocity, float deltaTime);

	//VARIABLES

	/// <summary>
	/// Quantit� de rotation sur les axes
	/// </summary>
	float w;

	/// <summary>
	/// Axe X
	/// </summary>
	float x;

	/// <summary>
	/// Axe Y
	/// </summary>
	float y;

	/// <summary>
	/// Axe Z
	/// </summary>
	float z;

};

