#pragma once
#include <iostream>
#include "Vector3D.h"
#include "Quaternion.h"

class Matrix3
{
public:
	//CONSTRUCTEURS

	/// <summary>
	/// Initialise une matrice identité 3x3
	/// </summary>
	Matrix3();

	// SURCHARGES D'OPERATEURS
	Matrix3 operator+(const Matrix3&);
	Matrix3 operator*(const Matrix3&);
	Vector3D operator*(const Vector3D&);
	friend std::ostream& operator<<(std::ostream& os, Matrix3 mat);

	// FONCTIONS

	/// <summary>
	/// Calcul de la matrice 3x3 pour un exposant donné
	/// </summary>
	/// <param name="exponent">Exposant donné</param>
	/// <returns>Matrice à la puissance indiquée</returns>
	Matrix3 pow(const int exponent);

	/// <summary>
	/// Calcul de la transposée de la matrice 3x3
	/// </summary>
	/// <returns>Matrice transposée</returns>
	Matrix3 Transpose();

	/// <summary>
	/// Calcul du déterminant de la matrice 3x3
	/// </summary>
	/// <returns>Déterminant de la matrice</returns>
	float Determinant();

	/// <summary>
	/// Calcul de la matrice inverse
	/// </summary>
	/// <param name="det">Déterminant de la matrice</param>
	/// <returns>Matrice inversée</returns>
	Matrix3 Inverse(float det);

	/// <summary>
	/// Conversion d'un quaternion en matrixe 3x3
	/// </summary>
	/// <param name="r">Quaternion à convertir</param>
	/// <returns>Matrice 3x3 convertie</returns>
	Matrix3 QuaternionToMatrix(Quaternion r);

	/// <summary>
	/// Modification manuelle d'une valeur de la matrice
	/// </summary>
	/// <param name="val">Valeur à assigner dans la matrice</param>
	/// <param name="col">Indice de la colonne de la matrice à modifier</param>
	/// <param name="row">Indice de la ligne de la matrice à modifier</param>
	void SetValue(float val, int col, int row);


private:
	/// <summary>
	/// Valeurs contenues dans la matrice
	/// </summary>
	float m[9];
};