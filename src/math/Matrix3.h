#pragma once
#include <iostream>
#include "Vector3D.h"
#include "Quaternion.h"

class Matrix3
{
public:
	Matrix3();

	Matrix3 operator+(const Matrix3&);
	Matrix3 operator*(const Matrix3&);
	Vector3D operator*(const Vector3D&);
	Matrix3 pow(const int exponent);
	Matrix3 Transpose();
	float Determinant();
	Matrix3 Inverse(float det);

	Matrix3 QuaternionToMatrix(Quaternion r);

	void SetValue(float val, int col, int row);

	friend std::ostream& operator<<(std::ostream& os, Matrix3 mat);

private:
	/// <summary>
	/// Valeurs contenues dans la matrice
	/// </summary>
	float m[9];
};