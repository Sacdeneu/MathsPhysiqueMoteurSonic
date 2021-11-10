#include "Matrix3.h"
#include "math.h"

Matrix3::Matrix3()
{
	m[0] = 1;
	m[1] = 0;
	m[2] = 0;

	m[3] = 0;
	m[4] = 1;
	m[5] = 0;

	m[6] = 0;
	m[7] = 0;
	m[8] = 1;
}

void Matrix3::SetValue(float val, int col, int row)
{
	m[col * 3 + row] = val;
}

Matrix3 Matrix3::operator+(const Matrix3& other)
{
	Matrix3 res;
	for (int i = 0; i < 9; i++)
		res.m[i] = m[i] + other.m[i];
	return res;
}

Matrix3 Matrix3::operator*(const Matrix3& other)
{
	Matrix3 res;

	res.m[0] = m[0] * other.m[0] + m[1] * other.m[3] + m[2] * other.m[6];
	res.m[1] = m[0] * other.m[1] + m[1] * other.m[4] + m[2] * other.m[7];
	res.m[2] = m[0] * other.m[2] + m[1] * other.m[5] + m[2] * other.m[8];
	
	res.m[3] = m[3] * other.m[0] + m[4] * other.m[3] + m[5] * other.m[6];
	res.m[4] = m[3] * other.m[1] + m[4] * other.m[4] + m[5] * other.m[7];
	res.m[5] = m[3] * other.m[2] + m[4] * other.m[5] + m[5] * other.m[8];

	res.m[6] = m[6] * other.m[0] + m[7] * other.m[3] + m[8] * other.m[6];
	res.m[7] = m[6] * other.m[1] + m[7] * other.m[4] + m[8] * other.m[7];
	res.m[8] = m[6] * other.m[2] + m[7] * other.m[5] + m[8] * other.m[8];

	return res;
}

Vector3D Matrix3::operator*(const Vector3D& other)
{
	Vector3D res;
	res.x = m[0] * other.x + m[1] * other.y + m[2] * other.z;
	res.y = m[3] * other.x + m[4] * other.y + m[5] * other.z;
	res.z = m[6] * other.x + m[7] * other.y + m[8] * other.z;
	return res;
}

Matrix3 Matrix3::pow(const int exponent)
{
	Matrix3 res;
	for (int i = 0; i < exponent; i++)
	{
		res = res * (const Matrix3&)*this;
	}
	return res;
}

std::ostream& operator<<(std::ostream& os, Matrix3 mat)
{
	char buffer[255];
	sprintf_s(buffer, "[%.2f  %.2f  %.2f]\n[%.2f  %.2f  %.2f]\n[%.2f  %.2f  %.2f]",
		mat.m[0], mat.m[1], mat.m[2],
		mat.m[3], mat.m[4], mat.m[5],
		mat.m[6], mat.m[7], mat.m[8]);
	os << buffer;
	return os;
}