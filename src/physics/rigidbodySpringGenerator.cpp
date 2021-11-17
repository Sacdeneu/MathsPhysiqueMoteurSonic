#include "rigidbodySpringGenerator.h"

RigidbodySpringGenerator::RigidbodySpringGenerator(Rigidbody* other, float length)
{
	this->other = other;
	k = 10.0f; // constante d'élasticité
	l0 = length;
}

void RigidbodySpringGenerator::UpdateForce(Rigidbody* rigidbody, float deltaTime)
{
	// Application de la loi de Hooke entre deux particules
	Vector3D diff = rigidbody->GetPosition() - other->GetPosition();
	float l = Vector3D::Norm(diff);
	Vector3D dir = Vector3D::Normalisation(diff);

	// On applique une force proportionnelle à l'étirement des deux objets (l0 - l)
	rigidbody->AddForce(dir * (k * (l0 - l)));
}