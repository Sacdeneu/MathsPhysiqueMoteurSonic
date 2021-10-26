#include "particleArchimedeGenerator.h"
#include "Vector3D.h"

#define GRAVITY -9.81f

ParticleArchimedeGenerator::ParticleArchimedeGenerator()
{
	depthMax = 2.0f;
	waterHeight = 5.0f;
	volumeObj = 1.0f;
	density = 1.0f;
	gravity = Vector3D(0, -GRAVITY, 0);
}

void ParticleArchimedeGenerator::UpdateForce(Particle* particle, float deltaTime)
{
	float radius = cbrt(particle->GetMass()) * 0.5f;
	volumeObj = (4 * 3.1415 * pow(radius, 3))/3;

	depthMax = waterHeight -(2 * radius);

	if (particle->GetPosition().y >= waterHeight + depthMax) {
		particle->AddForce(Vector3D(0, 0, 0));
	}
	else if (particle->GetPosition().y <= depthMax - waterHeight) {
		particle->AddForce(gravity * volumeObj * density);
	}
	else {
		float submersiveRation = abs(particle->GetPosition().y - waterHeight - depthMax);
		particle->AddForce(gravity * volumeObj * density * submersiveRation);
	}
}