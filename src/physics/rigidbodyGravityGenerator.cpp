#include "rigidbodyGravityGenerator.h"

#define GRAVITY -9.81f

RigidbodyGravityGenerator::RigidbodyGravityGenerator()
{
	gravity = Vector3D(0, GRAVITY, 0);
}

void RigidbodyGravityGenerator::UpdateForce(Rigidbody* rigidbody, float deltaTime)
{
	// On applique simplement la gravité sur le rigidbody en fonction de sa masse
	rigidbody->AddForce(gravity * rigidbody->GetMass());
	//rigidbody->AddForceAtPoint(gravity * rigidbody->GetMass(), Vector3D(10,0,0));
}