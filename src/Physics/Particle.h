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
	inline float GetInvMass() { return invMass; }
	inline float GetMass() { return 1.0f / invMass; }

	// Accesseur
	Vector3D GetPosition() { return position; }
	inline void SetPosition(Vector3D newPosition) { position = newPosition; }
	inline Vector3D GetVelocity() { return velocity; }
	inline float GetRadius() { return radius; }
	inline void AddForce(Vector3D force) { totalForce = totalForce + force; }
	inline void CleanTotalForce() { totalForce = Vector3D(0, 0, 0); }

protected: 
	Vector3D position;
	Vector3D velocity;
	float radius;
	float invMass;

public:
	int id;
	Vector3D totalForce;
	bool isBlob;
	bool isAABB;
};

