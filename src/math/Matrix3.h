#pragma once
#include <iostream>
using namespace std;

class Matrix3
{
public:
	Matrix3();

	Matrix3 operator+(const Matrix3&);
	Matrix3 operator*(const Matrix3&);

	void SetValue(float val, int col, int row);

	friend std::ostream& operator<<(std::ostream& os, Matrix3 mat);

private:
	/// <summary>
	/// Valeurs contenues dans la matrice
	/// </summary>
	float m[9];
};