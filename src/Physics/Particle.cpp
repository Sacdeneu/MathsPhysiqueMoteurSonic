#include "Particle.h"
#include "Math.h"
#include "Vector3D.h"


Particle::Particle()
{
	position = Vector3D(0, 0, 0);
	velocity = Vector3D(0, 0, 0);
	acceleration = Vector3D(0, 0, 0);

	damping = 0.95;
	mass = 1;
	size = 1;
	color = Vector3D(0, 0, 0);

}

Particle::Particle(Vector3D initialPos, float mass)
{
	position = initialPos;
	this->mass = mass;

	velocity = Vector3D(0, 0, 0);
	acceleration = Vector3D(0, 0, 0);
	damping = 0.95;

	size = 1;
	color = Vector3D(0, 0, 0);
}

/*Particle::~Particle()
{

}*/



void Particle::AddVelocity(Vector3D force)
{
	velocity = force;
}
void Particle::AddForce(Vector3D force) 
{
	acceleration = force * GetMass();
}

void Particle::Update(float deltaTime)
{
	// Update Position
	// Si je ne fais pas ça, ça ne compile pas
	Vector3D velocityDeltaTime = (velocity * deltaTime);
	Vector3D accelerationDeltaTime = acceleration * (powf(deltaTime, 2) / 2);

	position = position + velocityDeltaTime + accelerationDeltaTime;

	// Update Velocity
	// Si je ne fais pas ça, ça ne compile pas
	Vector3D accelerationTest = (acceleration * deltaTime);
	velocity = (velocity * powf(damping, deltaTime)) + accelerationTest;

}
