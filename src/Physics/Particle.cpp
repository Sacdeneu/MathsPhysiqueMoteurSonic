#include "Particle.h"



Particle::Particle()
{
	position = new Vector3D(0, 0, 0);
	velocity = new Vector3D(0, 0, 0);
	acceleration = new Vector3D(0, 0, 0);

	damping = 1;
	mass = 1;
	size = 1;
	color = new Vector3D(0, 0, 0);

}

Particle::Particle(Vector3D* initialPos, float mass)
{
	position = initialPos;
	this->mass = mass;

	velocity = new Vector3D(0, 0, 0);
	acceleration = new Vector3D(0, 0, 0);
	damping = 1;

	size = 1;
	color = new Vector3D(0, 0, 0);
}

void Particle::Update(float deltaTime)
{
 
}
