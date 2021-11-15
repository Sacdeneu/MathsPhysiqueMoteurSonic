#pragma once
#include <iostream>

class Quaternion
{
public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(const Quaternion&) = default;

	Quaternion operator*(const float&);
	Quaternion operator+(const Quaternion&);
	Quaternion operator-(const Quaternion&);
	Quaternion operator*(const Quaternion&);
	float& operator[](size_t index);
	const float& operator[](size_t index) const;



	void Normalize();
	Quaternion Normalize(Quaternion);
	void RotateByVector();
	void UpdateAngularVelocity(Quaternion angularVelocity, float deltaTime);


	friend std::ostream& operator<<(std::ostream& os, Quaternion mat);

	float w;
	float x;
	float y;
	float z;

};

