#include "ParticleContactGenerator.h"
#include "Math.h"

std::vector<ParticleContact*> ParticleContactGenerator::UpdateContactSphere(std::vector<Particle*> particles)
{
	std::vector<ParticleContact*> collisions;
	for (size_t i = 0; i < particles.size(); i++)
	{
		for (size_t j = 0; j < particles.size(); j++)
		{
			// On ne peut pas checker la collision avec les mêmes particles
			if (i != j) 
			{
				// Contact
				if (CheckSphereIntersection(particles[i], particles[j]))
				{
					Vector3D normal = Vector3D::Normalisation(particles[i]->GetPosition() - particles[j]->GetPosition());
					float interpenetration = particles[i]->GetRadius() * 0.5f + particles[j]->GetRadius() * 0.5f -
											 std::abs(Vector3D::Norm(particles[i]->GetPosition() - particles[j]->GetPosition()));
					
					std::cout << "Collision detected\n";
					std::cout << normal;
					std::cout << '\n';
					std::cout << interpenetration;
					std::cout << '\n';
					collisions.push_back(new ParticleContact(particles[i], particles[j], normal, interpenetration));
				}
			}
		}
	}
	return collisions;
}

bool ParticleContactGenerator::CheckSphereIntersection(Particle* A, Particle* B)
{
	float radius = A->GetRadius() * 0.5f + B->GetRadius() * 0.5f;
	float distance = std::abs(Vector3D::NormSquare(A->GetPosition() - B->GetPosition()));

	return (distance < radius);
}

bool ParticleContactGenerator::CheckSphereTransformIntersection(Particle* A, Transform* B)
{
	return false;
}
