#pragma once
#pragma once
#include <iostream>
using namespace std;


class Vector3D
{
	public:
		//VARIABLES

		/// <summary>
		/// Coordonnée sur l'axe x du vecteur
		/// </summary>
		float x;

		/// <summary>
		/// Coordonnée sur l'axe y du vecteur
		/// </summary>
		float y;

		/// <summary>
		/// Coordonnée sur l'axe z du vecteur
		/// </summary>
		float z;

		// SURCHARGES D'OPERATEURS
		Vector3D operator+(const Vector3D&);
		Vector3D operator-(const Vector3D&);
		Vector3D operator*(float);
		friend std::ostream& operator<<(std::ostream& os, Vector3D v);

		//CONSTRUCTEURS

		/// <summary>
		/// Initialise un vecteur en trois dimensions vide (0,0,0)
		/// </summary>
		Vector3D();

		/// <summary>
		/// Crée un vecteur en trois dimensions
		/// </summary>
		/// <param name="x">Coordonnée sur l'axe x du vecteur</param>
		/// <param name="y">Coordonnée sur l'axe y du vecteur</param>
		/// <param name="z">Coordonnée sur l'axe z du vecteur</param>
		Vector3D(float, float, float);

		//FONCTIONS

		/// <summary>
		/// Calcule la norme d'un vecteur
		/// </summary>
		/// <param name="vector">Vecteur dont on calcule la norme</param>
		/// <returns>Norme du vecteur</returns>
		static float Norm(Vector3D);

		/// <summary>
		/// Calcule le carré de la norme à partir d'un vecteur donné
		/// </summary>
		/// <param name="vector">Vecteur dont on calcule la norme au carré à partir du produit scalaire du vecteur avec lui même</param>
		/// <returns>Norme au carré</returns>
		static float NormSquare(Vector3D);

		/// <summary>
		/// Normalise un vecteur (division de chaque coordonnée par la norme)
		/// </summary>
		/// <param name="vector">Vecteur à normaliser</param>
		/// <returns>Vecteur normalisé</returns>
		static Vector3D Normalisation(Vector3D);

		/// <summary>
		/// Normalise un vecteur (division de chaque coordonnée par la norme)
		/// </summary>
		/// <returns>Vecteur normalisé</returns>
		Vector3D Normalisation();

		/// <summary>
		/// Multiplie un vecteur par un scalaire
		/// </summary>
		/// <param name="scalar">Scalaire</param>
		/// <returns>Vecteur multiplé par un scalaire</returns>
		Vector3D ScalarMultiply(float);

		/// <summary>
		/// Effectue une addition entre deux vecteurs
		/// </summary>
		/// <param name="vector">Vecteur à additionner</param>
		/// <returns>Vecteur somme</returns>
		Vector3D Addition(Vector3D);

		/// <summary>
		/// Soustrait deux vecteurs entre eux
		/// </summary>
		/// <param name="vector">Vecteur à soustraire</param>
		/// <returns>Vecteur somme</returns>
		Vector3D Substraction(Vector3D);

		/// <summary>
		/// Multiplie deux vecteurs entre eux
		/// </summary>
		/// <param name="vector1">Vecteur à multiplier</param>
		/// <returns>Vecteur somme</returns>
		Vector3D Multiply(Vector3D);

		/// <summary>
		/// Produit scalaire entre deux vecteurs (calcul valable uniquement dans un repère orthonormé)
		/// </summary>
		/// <param name="vector1">Premier vecteur du produit scalaire</param>
		/// <param name="vector2">Second vecteur du produit scalaire</param>
		/// <returns>Produit scalaire</returns>
		static float ScalarProduct(Vector3D, Vector3D);

		/// <summary>
		/// Produit vectoriel entre deux vecteurs
		/// </summary>
		/// <param name="vector1">Premier vecteur du produit vectoriel</param>
		/// <param name="vector2">Second vecteur du produit vectoriel</param>
		/// <returns>Vecteur résultat du produit vectoriel</returns>
		static Vector3D CrossProduct(Vector3D, Vector3D);
};

