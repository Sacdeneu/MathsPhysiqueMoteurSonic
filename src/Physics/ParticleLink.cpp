#include "ParticleLink.h"

ParticleLink::ParticleLink(Particle* A, Particle* B, float lengthLink)
{
	particles[0] = A;
	particles[1] = B;
	length = lengthLink;
}

ParticleContact* ParticleLink::CheckCollision()
{
	return NULL;
}
