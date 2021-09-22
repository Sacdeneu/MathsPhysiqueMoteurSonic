#include "Particle.h"
#include "Math.h"
#include "Vector3D.h"

#define GRAVITY 9.81f

Particle::Particle()
{
	position = Vector3D(0, 0, 0);
	velocity = Vector3D(0, 0, 0);
	acceleration = Vector3D(0, 0, 0);

	damping = 0.98f;
	invMass = 1;
	size = 1;
	color = Vector3D(0, 0, 0);
}

Particle::Particle(Vector3D initialPos, float mass)
{
	position = initialPos;
	this->invMass = mass;

	velocity = Vector3D(0, 0, 0);
	acceleration = Vector3D(0, 0, 0);
	damping = 0.98f;

	size = 1;
	color = Vector3D(0, 0, 0);
}

void Particle::SetMass(float newMass)
{
	if (newMass != 0)
		invMass = 1.0f / newMass;
	else
		invMass = 1; //valeur par défaut si newMass est nul
}

/*Particle::~Particle()
{

}*/

void Particle::SetVelocity(Vector3D newVelocity)
{
	velocity = newVelocity;
}

//accélération en m/s^2 donc la force ne rentre pas en compte ici
void Particle::SetAcceleration(Vector3D newAcceleration)
{
	acceleration = newAcceleration;
}

void Particle::Update(float dt)
{
	// Update Position
	Vector3D deltaPosition = (velocity * dt); //delta position = offset de la position d'une frame à l'autre
	position = position + deltaPosition;

	// Update Velocity
	Vector3D deltaVelocity = acceleration * dt; //delta velocity = difference de vélocité d'une frame à l'autre
	velocity = (velocity * powf(damping, dt)) + deltaVelocity; //on applique le damping

}
