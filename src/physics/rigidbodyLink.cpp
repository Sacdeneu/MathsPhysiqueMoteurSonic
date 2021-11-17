#include "rigidbodyLink.h"

RigidbodyLink::RigidbodyLink(Rigidbody* A, Rigidbody* B, float lengthLink)
{
	rigidbodys[0] = A;
	rigidbodys[1] = B;
	length = lengthLink;
}

RigidbodyContact* RigidbodyLink::CheckCollision()
{
	return NULL;
}
