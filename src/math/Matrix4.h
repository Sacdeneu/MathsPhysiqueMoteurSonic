#pragma once
#include <iostream>
#include "Vector3D.h"
#include "Quaternion.h"
#include <vector>
#include <glew.h>

class Matrix4
{
	public:

		//CONSTRUCTEURS

		/// <summary>
		/// Initialise une matrice identité 4x4
		/// </summary>
		Matrix4();

		/// <summary>
		/// Initalise une matrice 4x4 avec des paramètres donnés
		/// </summary>
		/// <param name="pos">Vecteur position</param>
		/// <param name="r">Quaternion orientation</param>
		/// <param name="scale">Vecteur scale</param>
		Matrix4(Vector3D pos, Quaternion r, Vector3D scale = Vector3D(1, 1, 1));


		// SURCHARGES D'OPERATEURS
		Matrix4 operator+(const Matrix4&);
		Matrix4 operator*(const Matrix4&);
		Vector3D operator*(const Vector3D& other);
		friend std::ostream& operator<<(std::ostream& os, Matrix4 mat);

		//FONCTIONS


		/// <summary>
		/// Modification manuelle d'une valeur de la matrice 4x4
		/// </summary>
		/// <param name="val">Valeur à assigner dans la matrice</param>
		/// <param name="col">Indice de la colonne de la matrice à modifier</param>
		/// <param name="row">Indice de la ligne de la matrice à modifier</param>
		void SetValue(float val, int col, int row);

		/// <summary>
		/// Mise à jour de la matrice transformation
		/// </summary>
		/// <param name="pos">Vecteur position</param>
		/// <param name="r">Quaternion orientation</param>
		/// <param name="scale">Vecteur scale</param>
		void UpdateTRS(Vector3D pos, Quaternion r, Vector3D scale = Vector3D(1, 1, 1));

		const GLfloat* GetGLMatrix();

		float Determinant();

		Matrix4 Inverse(float det);

	private:
		/// <summary>
		/// Valeurs contenues dans la matrice
		/// </summary>
		float m[16];
};

