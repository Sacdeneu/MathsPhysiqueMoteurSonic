#pragma once
#include "Vector3D.h"

class Particle
{
public:
	Particle();
	Particle(Vector3D* initialPos, float mass);
	//~Particle();

	//void Move();
	void Update(float deltaTime);



	inline Vector3D* GetPosition() { return position; }
	inline Vector3D* GetVelocity() { return velocity; }
	inline float GetDamping() { return damping; }
	inline float GetMass() { return 1/mass; }


private: 
	Vector3D* position;
	Vector3D* velocity;
	float damping;
	float mass;



public:

	Vector3D* acceleration;
	float size;
	Vector3D* color;

};

