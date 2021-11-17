#include "rigidbodyCable.h"

RigidbodyCable::RigidbodyCable(Rigidbody* A, Rigidbody* B, float length) : RigidbodyLink(A, B, length)
{
}

RigidbodyContact* RigidbodyCable::CheckCollision()
{
	Vector3D vectorDistance = rigidbodys[0]->GetPosition() - rigidbodys[1]->GetPosition();
	float distance = Vector3D::NormSquare(vectorDistance);

	// Si la distance entre les deux particules est plus grande que la longueur du câble, alors on applique une
	// collision pour faire rapprocher les particules
	if (distance > (length * length))
	{
		return new RigidbodyContact(rigidbodys[0], rigidbodys[1], Vector3D::Normalisation(-vectorDistance), 0, 0);
	}

	return NULL;

}
