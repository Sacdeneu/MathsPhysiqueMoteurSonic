#include "ParticleContactSolver.h"
#include "Math.h"

void ParticleContactSolver::UpdateCollisions(Scene* scene, int iterations)
{
	for (int i = 0; i < iterations; i++)
	{
		std::vector<ParticleContact>* contacts = generator.UpdateContacts(scene);
		std::cout << "Contacts : " << contacts->size() << std::endl;

		for (int j = 0; j < contacts->size(); j++)
		{
				std::cout << "    [" << j << "] Normal:" << (contacts->at(j).GetNormal())
					<< "; Interpenetration:" << (contacts->at(j).GetInterpenetration()) << std::endl;

		}
	}
}