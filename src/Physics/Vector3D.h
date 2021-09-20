#pragma once
#pragma once
#include <iostream>
using namespace std;


class Vector3D
{
	public:
		float x;
		float y;
		float z;
		Vector3D();
		Vector3D(float, float, float);
		float Norm(float, float, float);
		float NormSquare(float);
		float NormSquare(Vector3D);
		Vector3D Normalisation(float, Vector3D);
		Vector3D ScalarMultiply(float, Vector3D);
		Vector3D Addition(Vector3D, Vector3D);
		Vector3D Substraction(Vector3D, Vector3D);
		Vector3D Multiply(Vector3D, Vector3D);
		float ScalarProduct(Vector3D, Vector3D);
		Vector3D CrossProduct(Vector3D, Vector3D);
		Vector3D operator+(Vector3D&);
		Vector3D operator-(Vector3D&);
		Vector3D operator*(float);
		friend std::ostream & operator<<(std::ostream &os, Vector3D v);

};

