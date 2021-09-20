#include "Vector3D.h"
#include "math.h"

std::ostream & operator<<(std::ostream &os, Vector3D v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}

Vector3D Vector3D::operator+( Vector3D& vector){
	return Addition(*this, vector); 
}

Vector3D Vector3D::operator-(Vector3D& vector) {
	return Substraction(*this, vector);
}

Vector3D Vector3D::operator*(float scalar) {
	return ScalarMultiply(scalar , *this);
}

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

float Vector3D::Norm(float x, float y , float z)
{
	float norm = sqrt(x * x + y * y + z * z);
	return norm;
}

float Vector3D::NormSquare(float norm)
{
	float normSquare = norm * norm;
	return normSquare;
}

float Vector3D::NormSquare(Vector3D vector)
{
	float normSquare = x * x + y * y + z * z;
	return normSquare;
}

Vector3D Vector3D::Normalisation(float norm, Vector3D vector)
{
	float newX = vector.x / norm;
	float newY = vector.y / norm;
	float newZ = vector.z / norm;
	Vector3D newVectorNormalised = Vector3D(newX, newY, newZ);
	return newVectorNormalised;
}

Vector3D Vector3D::ScalarMultiply(float scalar, Vector3D vector)
{
	float newX = vector.x * scalar;
	float newY = vector.y * scalar;
	float newZ = vector.z * scalar;
	Vector3D newVector = Vector3D(newX, newY, newZ);
	return newVector;
}

Vector3D Vector3D::Addition(Vector3D vector1, Vector3D vector2)
{
	Vector3D newVector = Vector3D(vector1.x+vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);

	return Vector3D(newVector);
}

Vector3D Vector3D::Substraction(Vector3D vector1, Vector3D vector2)
{
	Vector3D newVector = Vector3D(vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z);

	return Vector3D(newVector);
}

Vector3D Vector3D::Multiply(Vector3D vector1, Vector3D vector2)
{
	Vector3D newVector = Vector3D(vector1.x * vector2.x, vector1.y * vector2.y, vector1.z * vector2.z);

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
