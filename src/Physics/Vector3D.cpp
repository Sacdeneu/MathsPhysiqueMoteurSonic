#include "Vector3D.h"
#include "math.h"

//VECTOR3D.CPP

// SURCHARGES D'OPERATEURS

std::ostream & operator<<(std::ostream &os, Vector3D v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}

Vector3D Vector3D::operator+(const Vector3D& vector){
	return Addition(vector); 
}

Vector3D Vector3D::operator-(const Vector3D& vector) {
	return Substraction(vector);
}


Vector3D Vector3D::operator*(float scalar) {
	return ScalarMultiply(scalar);
}

// CONSTRUCTEURS

Vector3D::Vector3D()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3D::Vector3D(float x, float y, float z)
{
	this->x= x;
	this->y = y;
	this->z = z;
}

// FONCTIONS

float Vector3D::Norm(Vector3D vector)
{
	float norm = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	return norm;
}

float Vector3D::NormSquare(Vector3D vector)
{
	float normSquare = vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
	return normSquare;
}


Vector3D Vector3D::Normalisation(Vector3D vector)
{
	float newX = vector.x / Norm(vector);
	float newY = vector.y / Norm(vector);
	float newZ = vector.z / Norm(vector);
	Vector3D newVectorNormalised = Vector3D(newX, newY, newZ);
	return newVectorNormalised;
}

Vector3D Vector3D::Normalisation()
{
	float newX = x / Norm(*this);
	float newY = y / Norm(*this);
	float newZ = z / Norm(*this);
	Vector3D newVectorNormalised = Vector3D(newX, newY, newZ);
	return newVectorNormalised;
}


Vector3D Vector3D::ScalarMultiply(float scalar)
{
	float newX = x * scalar;
	float newY = y * scalar;
	float newZ = z * scalar;
	Vector3D newVector = Vector3D(newX, newY, newZ);
	return newVector;
}


Vector3D Vector3D::Addition(Vector3D vectortoAdd)
{
	Vector3D newVector = Vector3D(x + vectortoAdd.x, y + vectortoAdd.y, z + vectortoAdd.z);

	return Vector3D(newVector);
}

Vector3D Vector3D::Substraction(Vector3D vectortoSubstract)
{
	Vector3D newVector = Vector3D(x - vectortoSubstract.x, y - vectortoSubstract.y, z - vectortoSubstract.z);

	return Vector3D(newVector);
}

Vector3D Vector3D::Multiply(Vector3D vectortoMultiply)
{
	Vector3D newVector = Vector3D(x * vectortoMultiply.x, y * vectortoMultiply.y, z * vectortoMultiply.z);

	return Vector3D(newVector);
}

float Vector3D::ScalarProduct(Vector3D vector1, Vector3D vector2)
{
	float scalarProduct = vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;

	return scalarProduct;

}

Vector3D Vector3D::CrossProduct(Vector3D vector1, Vector3D vector2)
{
	Vector3D crossProduct = Vector3D(vector1.y * vector2.z - vector1.z * vector2.y, vector1.z * vector2.x - vector1.x * vector2.z, vector1.x * vector2.y - vector1.y * vector2.x);

	return crossProduct;
}
