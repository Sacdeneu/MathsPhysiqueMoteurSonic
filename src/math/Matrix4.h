#pragma once
#include <iostream>
#include "Vector3D.h"
#include "Quaternion.h"
#include <vector>
using namespace std;

class Matrix4
{
	public:
		Matrix4();
		Matrix4(Vector3D pos, Quaternion r, Vector3D scale = Vector3D(1, 1, 1));

		Matrix4 operator+(const Matrix4&);
		Matrix4 operator*(const Matrix4&);

		void SetValue(float val, int col, int row);
		void UpdateTRS(Vector3D pos, Quaternion r, Vector3D scale = Vector3D(1, 1, 1));

		friend std::ostream& operator<<(std::ostream& os, Matrix4 mat);

	private:
		/// <summary>
		/// Valeurs contenues dans la matrice
		/// </summary>
		float m[16];
};

