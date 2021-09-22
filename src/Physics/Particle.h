#pragma once
#include "Vector3D.h"

class Particle
{
public:
	Particle();
	Particle(Vector3D initialPos, float mass);
	//~Particle();


	void Update(float deltaTime);
	void SetVelocity(Vector3D newVelocity);
	void SetAcceleration(Vector3D newAcceleration);

	inline void SetMass(float newMass);
	inline float GetMass() { return 1.0f / invMass; }

	// Accesseur
	inline Vector3D GetPosition() { return position; }
	inline Vector3D GetVelocity() { return velocity; }
	inline Vector3D GetAcceleration() { return acceleration; }
	inline float GetDamping() { return damping; }

private: 
	Vector3D position;
	Vector3D velocity;
	Vector3D acceleration;
	float damping;
	float invMass;



public:
	float size;
	Vector3D color;

};

