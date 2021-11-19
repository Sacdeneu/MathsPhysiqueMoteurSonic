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

Matrix3 Matrix3::Transpose() 
{
	Matrix3 res;
	res.m[0] = m[0];
	res.m[1] = m[3];
	res.m[2] = m[6];

	res.m[3] = m[1];
	res.m[4] = m[4];
	res.m[5] = m[7];

	res.m[6] = m[2];
	res.m[7] = m[5];
	res.m[8] = m[8];
	return res;
}

float Matrix3::Determinant()
{
	float det;
	det = m[0] * (m[4] * m[8] - m[7] * m[5]) - m[3] * (m[1] * m[8] - m[7] * m[2]) + m[6] * (m[1] * m[5] - m[4] * m[2]);
	return det;
}

Matrix3 Matrix3::Inverse(float det)
{
	if (det == 0) {
		std::cout << "ALLO";
	}
	Matrix3 res;
	float invDet = 1.0 / det;


	res.m[0] = (m[8] * m[4] - m[5] * m[7]) * invDet;
	res.m[1] = -(m[8] * m[1] - m[2] * m[7]) * invDet;
	res.m[2] = (m[5] * m[1] - m[2] * m[4]) * invDet;

	res.m[3] = -(m[8] * m[3] - m[5] * m[6]) * invDet;
	res.m[4] = (m[8] * m[0] - m[2] * m[6]) * invDet;
	res.m[5] = -(m[5] * m[0] - m[2] * m[3]) * invDet;

	res.m[6] = (m[7] * m[3] - m[4] * m[6]) * invDet;
	res.m[7] = -(m[7] * m[0] - m[1] * m[6]) * invDet;
	res.m[8] = (m[4] * m[0] - m[1] * m[3]) * invDet;

	return res;
}

Matrix3 Matrix3::QuaternionToMatrix(Quaternion r) 
{
	Matrix3 res;
	m[0] = 1 - 2 * (r.y * r.y + r.z * r.z);
	m[1] = 2 * (r.x * r.y + r.z * r.w);
	m[2] = 2 * (r.x * r.z - r.y * r.w);

	m[3] = 2 * (r.x * r.y - r.z * r.w);
	m[4] = 1 - 2 * (r.x * r.x + r.z * r.z);
	m[5] = 2 * (r.y * r.z + r.x * r.w);

	m[6] = 2 * (r.x * r.z + r.y * r.w);
	m[7] = 2 * (r.y * r.z - r.x * r.w);
	m[8] = 1 - 2 * (r.x * r.x + r.y * r.y);

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