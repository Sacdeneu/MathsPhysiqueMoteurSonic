#include "Vector3D.h"
#include "math.h"

//VECTOR3D.CPP

// SURCHARGES D'OPERATEURS

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

// CONSTRUCTEURS

/// <summary>
/// Initialise un vecteur en trois dimensions vide (0,0,0)
/// </summary>
Vector3D::Vector3D()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
/// <summary>
/// Crée un vecteur en trois dimensions
/// </summary>
/// <param name="x">Coordonnée sur l'axe x du vecteur</param>
/// <param name="y">Coordonnée sur l'axe y du vecteur</param>
/// <param name="z">Coordonnée sur l'axe z du vecteur</param>
Vector3D::Vector3D(float x, float y, float z)
{
	this->x= x;
	this->y = y;
	this->z = z;
}

// FONCTIONS

/// <summary>
/// Calcule la norme d'un vecteur à partir de ses coordonnées
/// </summary>
/// <param name="x">Coordonnée sur l'axe x du vecteur</param>
/// <param name="y">Coordonnée sur l'axe y du vecteur</param>
/// <param name="z">Coordonnée sur l'axe z du vecteur</param>
/// <returns>Norme du vecteur</returns>
float Vector3D::Norm(float x, float y , float z)
{
	float norm = sqrt(x * x + y * y + z * z);
	return norm;
}

/// <summary>
/// Calcule le carré de la norme à partir d'une norme donnée
/// </summary>
/// <param name="norm">Norme du vecteur</param>
/// <returns>Norme au carré</returns>
float Vector3D::NormSquare(float norm)
{
	float normSquare = norm * norm;
	return normSquare;
}

/// <summary>
/// Calcule le carré de la norme à partir d'un vecteur donné
/// </summary>
/// <param name="vector">Vecteur dont on calcule la norme au carré</param>
/// <returns>Norme au carré</returns>
float Vector3D::NormSquare(Vector3D vector)
{
	float normSquare = x * x + y * y + z * z;
	return normSquare;
}

/// <summary>
/// Normalise un vecteur (division de chaque coordonnée par la norme)
/// </summary>
/// <param name="norm">Norme du vecteur</param>
/// <param name="vector">Vecteur à normaliser</param>
/// <returns>Vecteur normalisé</returns>
Vector3D Vector3D::Normalisation(float norm, Vector3D vector)
{
	float newX = vector.x / norm;
	float newY = vector.y / norm;
	float newZ = vector.z / norm;
	Vector3D newVectorNormalised = Vector3D(newX, newY, newZ);
	return newVectorNormalised;
}

/// <summary>
/// Multiplie un vecteur par un scalaire
/// </summary>
/// <param name="scalar">Scalaire</param>
/// <param name="vector">Vecteur à multiplier</param>
/// <returns>Vecteur multiplé par un scalaire</returns>
Vector3D Vector3D::ScalarMultiply(float scalar, Vector3D vector)
{
	float newX = vector.x * scalar;
	float newY = vector.y * scalar;
	float newZ = vector.z * scalar;
	Vector3D newVector = Vector3D(newX, newY, newZ);
	return newVector;
}

/// <summary>
/// Effectue une addition entre deux vecteurs
/// </summary>
/// <param name="vector1">Premier vecteur à additionner</param>
/// <param name="vector2">Deuxième vecteur à additionner</param>
/// <returns>Vecteur somme</returns>
Vector3D Vector3D::Addition(Vector3D vector1, Vector3D vector2)
{
	Vector3D newVector = Vector3D(vector1.x+vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);

	return Vector3D(newVector);
}

/// <summary>
/// Soustrait deux vecteurs entre eux
/// </summary>
/// <param name="vector1">Premier vecteur à soustraire</param>
/// <param name="vector2">Deuxième vecteur à soustraire</param>
/// <returns>Vecteur somme</returns>
Vector3D Vector3D::Substraction(Vector3D vector1, Vector3D vector2)
{
	Vector3D newVector = Vector3D(vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z);

	return Vector3D(newVector);
}

/// <summary>
/// Multiplie deux vecteurs entre eux
/// </summary>
/// <param name="vector1">Premier vecteur à multiplier</param>
/// <param name="vector2">Second vecteur à multiplier</param>
/// <returns>Vecteur somme</returns>
Vector3D Vector3D::Multiply(Vector3D vector1, Vector3D vector2)
{
	Vector3D newVector = Vector3D(vector1.x * vector2.x, vector1.y * vector2.y, vector1.z * vector2.z);

	return Vector3D(newVector);
}

/// <summary>
/// Produit scalaire entre deux vecteurs (calcul valable uniquement dans un repère orthonormé)
/// </summary>
/// <param name="vector1">Premier vecteur du produit scalaire</param>
/// <param name="vector2">Second vecteur du produit scalaire</param>
/// <returns>Produit scalaire</returns>
float Vector3D::ScalarProduct(Vector3D vector1, Vector3D vector2)
{
	float scalarProduct = vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;

	return scalarProduct;

}

/// <summary>
/// Produit vectoriel entre deux vecteurs
/// </summary>
/// <param name="vector1">Premier vecteur du produit vectoriel</param>
/// <param name="vector2">Second vecteur du produit vectoriel</param>
/// <returns>Vecteur résultat du produit vectoriel</returns>
Vector3D Vector3D::CrossProduct(Vector3D vector1, Vector3D vector2)
{
	Vector3D crossProduct = Vector3D(vector1.y * vector2.z - vector1.z * vector2.y, vector1.z * vector2.x - vector1.x * vector2.z, vector1.x * vector2.y - vector1.y * vector2.x);

	return crossProduct;
}
