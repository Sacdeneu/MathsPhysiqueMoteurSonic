#include "rigidbodyAnchoredSpringGenerator.h"

RigidbodyAnchoredSpringGenerator::RigidbodyAnchoredSpringGenerator(Vector3D pos, float length)
{
	anchorPoint = pos;
	k = 10.0f; // constante d'élasticité
	l0 = length;
}

void RigidbodyAnchoredSpringGenerator::UpdateForce(Rigidbody* rigidbody, float deltaTime)
{
	// Application de la loi de Hooke entre un rigidbody et point d'ancrage (statique)
	Vector3D diff = rigidbody->GetPosition() - anchorPoint;
	float l = Vector3D::Norm(diff);
	Vector3D dir = Vector3D::Normalisation(diff);

	// On applique une force proportionnelle à l'étirement des deux objets (l0 - l)
	rigidbody->AddForce(dir * (k * (l0 - l)));
}