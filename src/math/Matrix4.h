#pragma once
#include <iostream>
using namespace std;

class Matrix4
{
	public:
		Matrix4();

		Matrix4 operator+(const Matrix4&);
		Matrix4 operator*(const Matrix4&);

		void SetValue(float val, int col, int row);

		friend std::ostream& operator<<(std::ostream& os, Matrix4 mat);

	private:
		/// <summary>
		/// Valeurs contenues dans la matrice
		/// </summary>
		float m[16];
};

