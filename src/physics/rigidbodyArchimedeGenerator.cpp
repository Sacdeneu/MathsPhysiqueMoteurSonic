#include "rigidbodyArchimedeGenerator.h"

#define GRAVITY -9.81f

RigidbodyArchimedeGenerator::RigidbodyArchimedeGenerator()
{
	depthMax = 2.0f;
	waterHeight = 5.0f;
	volumeObj = 1.0f;
	density = 1.0f;
	gravity = Vector3D(0, -GRAVITY, 0);
}

void RigidbodyArchimedeGenerator::UpdateForce(Rigidbody* rigidbody, float deltaTime)
{
	// On calcule le volume de notre particule
	float radius = cbrt(rigidbody->GetMass()) * 0.5f;
	volumeObj = (4 * 3.1415 * pow(radius, 3))/3;

	// On calcule la profondeur max de l'eau
	depthMax = waterHeight -(2 * radius);

	if (rigidbody->GetPosition().y >= waterHeight + depthMax) { // Si l'objet est hors de l'eau, on applique aucune force
		rigidbody->AddForce(Vector3D(0, 0, 0));
	}
	else if (rigidbody->GetPosition().y <= depthMax - waterHeight) { // Si elle est complètement dans l'eau, on applique une force constante par à rapport à son volume
		rigidbody->AddForce(gravity * volumeObj * density);
	}
	else { // Sinon on applique une force proportionnelle à son ratio de submersion.
		float submersiveRation = abs(rigidbody->GetPosition().y - waterHeight - depthMax);
		rigidbody->AddForce(gravity * volumeObj * density * submersiveRation);
	}
}