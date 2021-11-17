#ifndef rigidbodyFORCEGENERATOR_H
#define rigidbodyFORCEGENERATOR_H

#include "rigidbody.h"

class RigidbodyForceGenerator
{
public:
	virtual void UpdateForce(Rigidbody* rigidbody, float deltaTime) = 0;
};
#endif

