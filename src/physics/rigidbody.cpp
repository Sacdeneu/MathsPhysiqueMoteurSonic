#include "rigidbody.h"
#include "Math.h"
#include "../rendering/scene.h"

int rigidbodyCounter = 0;

Rigidbody::Rigidbody()
{
	id = rigidbodyCounter++;

	position = Vector3D(0, 0, 0);
	velocity = Vector3D(0, 0, 0);

	orientation = Quaternion();
	angularVelocity = Vector3D(0, 0, 0);
	transformMatrix = Matrix4(position, orientation);

	isBlob, isAABB = false; // flag utilisé pour le blob
	SetMass(1);

}

Rigidbody::Rigidbody(Vector3D initialPos, float mass)
{
	id = rigidbodyCounter++;

	position = initialPos;
	SetMass(mass);
	isBlob, isAABB = false; // flag utilisé pour le blob
	velocity = Vector3D(0, 0, 0);
}

void Rigidbody::SetMass(float newMass)
{
	if (newMass != 0)
		invMass = 1.0f / newMass;
	else
		invMass = 1; //valeur par défaut si newMass est nul

	//toutes les particules ont une densité constante,
	//on calcule le rayon comme étant la racine cubique de la masse afin que la masse paraisse visuellement correcte
	radius = cbrt(newMass) * 0.5f;
}

/*rigidbody::~rigidbody()
{

}*/

void Rigidbody::SetVelocity(Vector3D newVelocity)
{
	velocity = newVelocity;
}

void Rigidbody::CalculDerivedData()
{
	// Update matrice transform
	transformMatrix.UpdateTRS(position, orientation);

	//inertiaTensor = matrixTransform
}

void Rigidbody::Update(float dt)
{
	// Update Position
	Vector3D deltaPosition = (velocity * dt); //delta position = offset de la position d'une frame à l'autre
	position = position + deltaPosition;

	// Update Velocity
	Vector3D acceleration = totalForce * invMass;
	Vector3D deltaVelocity = acceleration * dt; //delta velocity = difference de vélocité d'une frame à l'autre
	velocity = velocity + deltaVelocity;

	CleanTotalForce();
	CalculDerivedData();

	if (position.y < -100)
		Scene::mainScene->Removerigidbody(this);
}
