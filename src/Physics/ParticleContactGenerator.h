#pragma once
#include "Vector3D.h"
#include "Particle.h"
#include "ParticleContact.h"
#include "../rendering/scene.h" // Pour choper les transform
#include <vector>

class ParticleContactGenerator
{
public:
	ParticleContactGenerator() = default;
	~ParticleContactGenerator() = default;


	// Fonction pour les collisions entre les sphères
	std::vector<ParticleContact*> UpdateContactSphere(std::vector<Particle*> particles);
	// Fonction pour les collisions entre les sphères et les transforms
	std::vector<ParticleContact*> UpdateContactSphereTransform(std::vector<Particle*> particles, std::vector<Transform> transforms);

private:
	// Check si 2 sphère se superposent
	bool CheckSphereIntersection(Particle* A, Particle* B);
	// Check si une sphere et un cube se surperpose
	bool CheckSphereTransformIntersection(Particle* A, Transform B);
};
