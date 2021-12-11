#include "Matrix4.h"
#include "math.h"

Matrix4::Matrix4()
{
	m[0] = 1;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;

	m[4] = 0;
	m[5] = 1;
	m[6] = 0;
	m[7] = 0;

	m[8] = 0;
	m[9] = 0;
	m[10] = 1;
	m[11] = 0;

	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
}


// Matrice de transformation
Matrix4::Matrix4(Vector3D pos, Quaternion r, Vector3D scale)
{
	UpdateTRS(pos, r, scale);

	m[3] = 0;
	m[7] = 0;
	m[11] = 0;
	m[15] = 1;
}

void Matrix4::SetValue(float val, int col, int row)
{
	m[col * 4 + row] = val;
}

// Update la matrice de transformation
void Matrix4::UpdateTRS(Vector3D pos, Quaternion r, Vector3D scale)
{
	m[0] = (1 - 2 * (r.y * r.y + r.z * r.z)) * scale.x;
	m[4] = (2 * (r.x * r.y + r.z * r.w)) * scale.x;
	m[8] = (2 * (r.x * r.z - r.y * r.w)) * scale.x;
	m[12] = pos.x;

	m[1] = (2 * (r.x * r.y - r.z * r.w)) * scale.y;
	m[5] = (1 - 2 * (r.x * r.x + r.z * r.z)) * scale.y;
	m[9] = (2 * (r.y * r.z + r.x * r.w)) * scale.y;
	m[13] = pos.y;

	m[2] = (2 * (r.x * r.z + r.y * r.w)) * scale.z;
	m[6] = (2 * (r.y * r.z - r.x * r.w)) * scale.z;
	m[10] = (1 - 2 * (r.x * r.x + r.y * r.y)) * scale.z;
	m[14] = pos.z;
}

Matrix4 Matrix4::operator+(const Matrix4& other)
{
	Matrix4 res;
	for (int i = 0; i < 16; i++)
		res.m[i] = m[i] + other.m[i];
	return res;
}

Matrix4 Matrix4::operator*(const Matrix4& other)
{
	Matrix4 res;

	res.m[0] = m[0] * other.m[0] + m[1] * other.m[4] + m[2] * other.m[8] + m[3] * other.m[12];
	res.m[1] = m[0] * other.m[1] + m[1] * other.m[5] + m[2] * other.m[9] + m[3] * other.m[13];
	res.m[2] = m[0] * other.m[2] + m[1] * other.m[6] + m[2] * other.m[10] + m[3] * other.m[14];
	res.m[3] = m[0] * other.m[3] + m[1] * other.m[7] + m[2] * other.m[11] + m[3] * other.m[15];

	res.m[4] = m[4] * other.m[0] + m[5] * other.m[4] + m[6] * other.m[8] + m[7] * other.m[12];
	res.m[5] = m[4] * other.m[1] + m[5] * other.m[5] + m[6] * other.m[9] + m[7] * other.m[13];
	res.m[6] = m[4] * other.m[2] + m[5] * other.m[6] + m[6] * other.m[10] + m[7] * other.m[14];
	res.m[7] = m[4] * other.m[3] + m[5] * other.m[7] + m[6] * other.m[11] + m[7] * other.m[15];

	res.m[8] = m[8] * other.m[0] + m[9] * other.m[4] + m[10] * other.m[8] + m[11] * other.m[12];
	res.m[9] = m[8] * other.m[1] + m[9] * other.m[5] + m[10] * other.m[9] + m[11] * other.m[13];
	res.m[10] = m[8] * other.m[2] + m[9] * other.m[6] + m[10] * other.m[10] + m[11] * other.m[14];
	res.m[11] = m[8] * other.m[3] + m[9] * other.m[7] + m[10] * other.m[11] + m[11] * other.m[15];

	res.m[12] = m[12] * other.m[0] + m[13] * other.m[4] + m[14] * other.m[8] + m[15] * other.m[12];
	res.m[13] = m[12] * other.m[1] + m[13] * other.m[5] + m[14] * other.m[9] + m[15] * other.m[13];
	res.m[14] = m[12] * other.m[2] + m[13] * other.m[6] + m[14] * other.m[10] + m[15] * other.m[14];
	res.m[15] = m[12] * other.m[3] + m[13] * other.m[7] + m[14] * other.m[11] + m[15] * other.m[15];

	return res;
}

const GLfloat* Matrix4::GetGLMatrix()
{
	//std::cout << (Matrix4)*this;
	return (GLfloat*)&m;
}

float Matrix4::Determinant()
{
	float det;
	float a00 = m[0],
		a01 = m[1],
		a02 = m[2],
		a03 = m[3];
	float a10 = m[4],
		a11 = m[5],
		a12 = m[6],
		a13 = m[7];
	float a20 = m[8],
		a21 = m[9],
		a22 = m[10],
		a23 = m[11];
	float a30 = m[12],
		a31 = m[13],
		a32 = m[14],
		a33 = m[15];

	float b00 = a00 * a11 - a01 * a10;
	float b01 = a00 * a12 - a02 * a10;
	float b02 = a00 * a13 - a03 * a10;
	float b03 = a01 * a12 - a02 * a11;
	float b04 = a01 * a13 - a03 * a11;
	float b05 = a02 * a13 - a03 * a12;
	float b06 = a20 * a31 - a21 * a30;
	float b07 = a20 * a32 - a22 * a30;
	float b08 = a20 * a33 - a23 * a30;
	float b09 = a21 * a32 - a22 * a31;
	float b10 = a21 * a33 - a23 * a31;
	float b11 = a22 * a33 - a23 * a32;

	det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;
	return det;
}

Matrix4 Matrix4::Inverse(float det)
{
	if (det == 0) {
		std::cout << "Je ne suis pas inversible";
	}
	Matrix4 res;
	float invDet = 1.0 / det;

	float a00 = m[0],
		a01 = m[1],
		a02 = m[2],
		a03 = m[3];
	float a10 = m[4],
		a11 = m[5],
		a12 = m[6],
		a13 = m[7];
	float a20 = m[8],
		a21 = m[9],
		a22 = m[10],
		a23 = m[11];
	float a30 = m[12],
		a31 = m[13],
		a32 = m[14],
		a33 = m[15];

	float b00 = a00 * a11 - a01 * a10;
	float b01 = a00 * a12 - a02 * a10;
	float b02 = a00 * a13 - a03 * a10;
	float b03 = a01 * a12 - a02 * a11;
	float b04 = a01 * a13 - a03 * a11;
	float b05 = a02 * a13 - a03 * a12;
	float b06 = a20 * a31 - a21 * a30;
	float b07 = a20 * a32 - a22 * a30;
	float b08 = a20 * a33 - a23 * a30;
	float b09 = a21 * a32 - a22 * a31;
	float b10 = a21 * a33 - a23 * a31;
	float b11 = a22 * a33 - a23 * a32;

	res.m[0] = (a11 * b11 - a12 * b10 + a13 * b09) * invDet;
	res.m[1] = (a02 * b10 - a01 * b11 - a03 * b09) * invDet;
	res.m[2] = (a31 * b05 - a32 * b04 + a33 * b03) * invDet;
	res.m[3] = (a22 * b04 - a21 * b05 - a23 * b03) * invDet;
	res.m[4] = (a12 * b08 - a10 * b11 - a13 * b07) * invDet;
	res.m[5] = (a00 * b11 - a02 * b08 + a03 * b07) * invDet;
	res.m[6] = (a32 * b02 - a30 * b05 - a33 * b01) * invDet;
	res.m[7] = (a20 * b05 - a22 * b02 + a23 * b01) * invDet;
	res.m[8] = (a10 * b10 - a11 * b08 + a13 * b06) * invDet;
	res.m[9] = (a01 * b08 - a00 * b10 - a03 * b06) * invDet;
	res.m[10] = (a30 * b04 - a31 * b02 + a33 * b00) * invDet;
	res.m[11] = (a21 * b02 - a20 * b04 - a23 * b00) * invDet;
	res.m[12] = (a11 * b07 - a10 * b09 - a12 * b06) * invDet;
	res.m[13] = (a00 * b09 - a01 * b07 + a02 * b06) * invDet;
	res.m[14] = (a31 * b01 - a30 * b03 - a32 * b00) * invDet;
	res.m[15] = (a20 * b03 - a21 * b01 + a22 * b00) * invDet;

	return res;
}

std::ostream& operator<<(std::ostream& os, Matrix4 mat)
{
	char buffer[255];
	sprintf_s(buffer,"[%.2f  %.2f  %.2f  %.2f]\n[%.2f  %.2f  %.2f  %.2f]\n[%.2f  %.2f  %.2f  %.2f]\n[%.2f  %.2f  %.2f  %.2f]",
		mat.m[0], mat.m[1], mat.m[2], mat.m[3],
		mat.m[4], mat.m[5], mat.m[6], mat.m[7],
		mat.m[8], mat.m[9], mat.m[10], mat.m[11],
		mat.m[12], mat.m[13], mat.m[14], mat.m[15]);
	os << buffer;
	return os;
}