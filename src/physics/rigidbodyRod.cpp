#include "rigidbodyRod.h"

RigidbodyRod::RigidbodyRod(Rigidbody* A, Rigidbody* B, float length) : RigidbodyLink(A, B, length)
{
}

RigidbodyContact* RigidbodyRod::CheckCollision()
{
	// Calcul de la distance entre les 2 rigidbodys.
	Vector3D vectorDistance = rigidbodys[0]->GetPosition() - rigidbodys[1]->GetPosition();
	float distance = Vector3D::NormSquare(vectorDistance);

	// Si la distance entre les deux rigidbodys est différente de la longueur du câble, alors on applique soit
	// une collision pour que les deux rigidbodys se rejoignent, soit pour qu'elles s'éloignent.
	if (distance > (length * length))
	{
		return new RigidbodyContact(rigidbodys[0], rigidbodys[1], Vector3D::Normalisation(-vectorDistance), 0, 0);
	}
	else  
	{
		return new RigidbodyContact(rigidbodys[0], rigidbodys[1], Vector3D::Normalisation(vectorDistance), 0, 0);
	}
	
	return NULL;

}
