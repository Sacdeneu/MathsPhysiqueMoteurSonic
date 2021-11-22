#include "rigidbodyBungeeGenerator.h"

RigidbodyBungeeGenerator::RigidbodyBungeeGenerator(Rigidbody* other, float length)
{
	this->other = other;
	k = 10.0f; // constante d'élasticité
	l0 = length;
}

void RigidbodyBungeeGenerator::UpdateForce(Rigidbody* rigidbody, float deltaTime)
{
	// Application de la loi de Hooke entre deux rigidbodys
	Vector3D diff = rigidbody->GetPosition() - other->GetPosition();
	float l = Vector3D::Norm(diff);
	Vector3D dir = Vector3D::Normalisation(diff);

	// Applique uniquement la force durant l'extension de l'élastique
	if (l0 < l) 
	{
		// On applique une force proportionnelle à l'étirement des deux objets (l0 - l)
		rigidbody->AddForce(dir * (k * (l0 - l)));
	}
}