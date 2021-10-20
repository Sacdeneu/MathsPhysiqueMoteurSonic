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

	inline void SetMass(float newMass);
	inline float GetMass() { return 1.0f / invMass; }

	// Accesseur
	inline Vector3D GetPosition() { return position; }
	inline Vector3D GetVelocity() { return velocity; }
	inline float GetRadius() { return radius; }
	inline void AddForce(Vector3D force) { totalForce = totalForce + force; }
	inline void CleanTotalForce() { totalForce = Vector3D(0, 0, 0); }

private: 
	Vector3D position;
	Vector3D velocity;
	float radius;
	float invMass;

public:
	int id;
	Vector3D totalForce;
};

