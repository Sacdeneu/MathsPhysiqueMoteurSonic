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
		Matrix4(Vector3D pos, Quaternion r, Vector3D scale = Vector3D(1, 1, 1));


		// SURCHARGES D'OPERATEURS
		Matrix4 operator+(const Matrix4&);
		Matrix4 operator*(const Matrix4&);
		friend std::ostream& operator<<(std::ostream& os, Matrix4 mat);

		//FONCTIONS

		void SetValue(float val, int col, int row);
		void UpdateTRS(Vector3D pos, Quaternion r, Vector3D scale = Vector3D(1, 1, 1));

		const GLfloat* GetGLMatrix();

	private:
		/// <summary>
		/// Valeurs contenues dans la matrice
		/// </summary>
		float m[16];
};

