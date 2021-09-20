#pragma once
#include "Vector3D.h"

class Particle
{
public:
	Particle();
	Particle(Vector3D initialPos, float mass);
	//~Particle();


	void Update(float deltaTime);
	void AddVelocity(Vector3D force);
	void AddForce(Vector3D force);

	// Accesseur
	inline Vector3D GetPosition() { return position; }
	inline Vector3D GetVelocity() { return velocity; }
	inline Vector3D GetAcceleration() { return acceleration; }
	inline float GetDamping() { return damping; }
	inline float GetMass() { return 1/mass; }


private: 
	Vector3D position;
	Vector3D velocity;
	Vector3D acceleration;
	float damping;
	float mass;



public:
	float size;
	Vector3D color;

};

