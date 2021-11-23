#include "rigidbody.h"
#include "Math.h"
#include "../rendering/scene.h"

int rigidbodyCounter = 0;

Rigidbody::Rigidbody()
{
	id = rigidbodyCounter++;

	position = Vector3D(0, 0, 0);
	velocity = Vector3D(0, 0, 0);

	angularVelocity = Vector3D(0, 0, 0);
	orientation = Quaternion();
	transformMatrix = Matrix4(position, orientation);

	isBlob, isAABB = false; // flag utilisé pour le blob
	SetMass(1);

	// Initialise un tenseur d'iniertie, ici on utilise le tenseur d'inertie du rectangle
	inverseInertiaTensor = Matrix3();
	inverseInertiaTensor.SetValue((1 / 12.0f) * GetMass() * (radius * radius + radius * radius), 0, 0);
	inverseInertiaTensor.SetValue((1 / 12.0f) * GetMass() * (radius * radius + radius * radius), 1, 1);
	inverseInertiaTensor.SetValue((1 / 12.0f) * GetMass() * (radius * radius + radius * radius), 2, 2);
	inverseInertiaTensor.Inverse(inverseInertiaTensor.Determinant());



}

Rigidbody::Rigidbody(Vector3D initialPos, float mass)
{
	id = rigidbodyCounter++;

	position = initialPos;
	SetMass(mass);
	isBlob, isAABB = false; // flag utilisé pour le blob
	velocity = Vector3D(0, 0, 0);

	angularVelocity = Vector3D(0, 0, 0);
	orientation = Quaternion();
	transformMatrix = Matrix4(position, orientation);

	// Initialise un tenseur d'iniertie, ici on utilise le tenseur d'inertie du rectangle
	inverseInertiaTensor = Matrix3();
	inverseInertiaTensor.SetValue((1 / 12.0f) * GetMass() * (radius * radius + radius * radius), 0, 0);
	inverseInertiaTensor.SetValue((1 / 12.0f) * GetMass() * (radius * radius + radius * radius), 1, 1);
	inverseInertiaTensor.SetValue((1 / 12.0f) * GetMass() * (radius * radius + radius * radius), 2, 2);
	inverseInertiaTensor.Inverse(inverseInertiaTensor.Determinant());
}

void Rigidbody::SetMass(float newMass)
{
	if (newMass != 0)
		invMass = 1.0f / newMass;
	else
		invMass = 1; //valeur par défaut si newMass est nul

	//toutes les rigidbodys ont une densité constante,
	//on calcule le rayon comme étant la racine cubique de la masse afin que la masse paraisse visuellement correcte
	radius = cbrt(newMass) * 0.5f;
}


void Rigidbody::SetVelocity(Vector3D newVelocity)
{
	velocity = newVelocity;
}

void Rigidbody::CalculDerivedData()
{
	// Mise à jour de matrice transform
	transformMatrix.UpdateTRS(position, orientation, Vector3D(radius, radius, radius));

	// Mise à jour du tenseur d'inertie en fonction de la matrice transform
	Matrix3 transformMatrix3;
	transformMatrix3.QuaternionToMatrix(orientation);

	if(transformMatrix3.Determinant() != 0)
		inverseInertiaTensorWorld = transformMatrix3 * inverseInertiaTensor * transformMatrix3.Inverse(transformMatrix3.Determinant());
}

void Rigidbody::AddForceAtPoint(Vector3D force, Vector3D point)
{
	// Convertir point en coordonnée relative à l'objet

	// Ajoute une force à l'objet par rapport à la position point
	AddForce(force);
	totalTorque = totalTorque + Vector3D::CrossProduct(point, force);
}

void Rigidbody::AddForceAtBodyPoint(Vector3D force, Vector3D point)
{
	// Convertir point en monde
	//point = transformMatrix * point;

	AddForceAtPoint(force, point);
}

void Rigidbody::Update(float dt)
{
	// Update Acceleration
	Vector3D accelerationAngular = inverseInertiaTensorWorld * totalTorque;


	// Update Velocity
	Vector3D acceleration = totalForce * invMass;
	Vector3D deltaVelocity = acceleration * dt; //delta velocity = difference de vélocité d'une frame à l'autre
	velocity = velocity + deltaVelocity;

	// Update Angular Velocity
	angularVelocity = angularVelocity + accelerationAngular * dt;
	Quaternion qAngularVelocity(angularVelocity.x, angularVelocity.y, angularVelocity.z, 0);

	// Drag
	// (on fait pas)

	// Update Position
	Vector3D deltaPosition = (velocity * dt); //delta position = offset de la position d'une frame à l'autre
	position = position + deltaPosition;

	// Update Orientation
	orientation.UpdateAngularVelocity(qAngularVelocity, dt);
	orientation.Normalize();

	// Calculate Derived Data
	CalculDerivedData();

	std::cout << angularVelocity;
	// Clear
	CleanTotalForce();
	CleanTotalTorque();

	if (position.y < -100)
		Scene::mainScene->RemoveRigidbody(this);
}
