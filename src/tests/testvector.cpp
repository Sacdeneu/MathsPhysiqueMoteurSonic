#include "../Physics/Vector3D.h"

int main(int argc, char* args[])
{
	Vector3D vector1 = Vector3D(1, 2, 3);
	Vector3D vector2 = Vector3D(4, 5, 6);
	Vector3D vector3 = vector1 + vector2;
	Vector3D vector4 = vector1 - vector2;
	std::cout << "Norm " << Vector3D::Norm(vector1) << std::endl;
	std::cout << "NormSquare " << Vector3D::NormSquare(vector1) << std::endl;
	std::cout << "Normalisation " << Vector3D::Normalisation(vector1) << std::endl;
	std::cout << "Normalisation 2 " << vector1.Normalisation() << std::endl;
	std::cout << "ScalarMultiply " << vector1.ScalarMultiply(5.0) << std::endl;
	std::cout << "Addition " << vector1.Addition(vector2) << std::endl;
	std::cout << "Substraction " << vector1.Substraction(vector2) << std::endl;
	std::cout << "Multiply " << vector1.Multiply(vector2) << std::endl;
	std::cout << "ScalarProduct " << Vector3D::ScalarProduct(vector1, vector2) << std::endl;
	std::cout << "CrossProduct " << Vector3D::CrossProduct(vector1, vector2) << std::endl;
	std::cout << "Vector3 Addition " << vector3 << std::endl;
	std::cout << "Vector4 Substraction " << vector4 << std::endl;
	return 0;
}