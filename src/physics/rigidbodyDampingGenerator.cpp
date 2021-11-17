#include "rigidbodyDampingGenerator.h"

RigidbodyDampingGenerator::RigidbodyDampingGenerator()
{
	// Valeurs arbitraires qui rendent bien à l'écran
	k1 = 0.1f;
	k2 = 0.01f;
}

void RigidbodyDampingGenerator::UpdateForce(Rigidbody* rigidbody, float deltaTime)
{
	Vector3D velocity = rigidbody->GetVelocity();
	rigidbody->AddForce(-velocity.Normalisation()*(k1*Vector3D::Norm(velocity)+k2*Vector3D::NormSquare(velocity)));
}
