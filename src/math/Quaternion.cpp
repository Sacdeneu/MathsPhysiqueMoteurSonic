#include "Quaternion.h"
#include "math.h"

Quaternion::Quaternion()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 1;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Quaternion Quaternion::operator*(const float& f)
{
    return Quaternion(x * f, y * f, z * f, w * f);
}

Quaternion Quaternion::operator+(const Quaternion& q)
{
    return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
}

Quaternion Quaternion::operator-(const Quaternion& q)
{
    return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
}


Quaternion Quaternion::operator*(const Quaternion& b)
{
    float newW = w * w - x * b.x - y * b.y - z * b.z;
    float newX = w * b.x + x * b.w + y * b.z - z * b.y;
    float newY = w * b.y + y * b.w + z * b.x - x * b.z;
    float newZ = w * b.z + z * b.w + x * b.y - y * b.x;

    return Quaternion(newX, newY, newZ, newW);
}


Vector3D Quaternion::operator*(const Vector3D& v)
{
    // On convertit le quaternion en matrix et on la multiplie à v
    float vectorX = (1.0f - 2 * (y*y + z*z)) * v.x +    2 * (x*y - z*w) * v.y +             2 * (x*z + w*y) * v.z;
    float vectorY = 2 * (x*y + z*w) * v.x +             (1.0f - 2 * (x*x + z*z)) * v.y +    2 * (y*z - w*x) * v.z;
    float vectorZ = 2 * (x*z - w*y) * v.x +             2 * (y*z + w*x) * v.y +             (1.0f - 2 * (x*x + y*y)) * v.z;
    return Vector3D(vectorX, vectorY, vectorZ);
}

float& Quaternion::operator[](size_t index)
{
    switch (index) 
    {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
    }
    // Renvoyé index out of range
    return x;
}

const float& Quaternion::operator[](size_t index) const
{
    switch (index)
    {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
    }
    return 0.0f;
}

void Quaternion::Normalize()
{
    *this = Normalize(*this);
}

Quaternion Quaternion::Normalize(Quaternion q)
{
    float norm = sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
    std::cout << '\n';
    std::cout << norm;
    std::cout << '\n';
    if (norm <= 0.01f)
        return Quaternion();
    return Quaternion(q.x / norm, q.y / norm, q.z / norm, q.w / norm);
}

void Quaternion::RotateByVector()
{

}

void Quaternion::UpdateAngularVelocity(Quaternion angularVelocity, float deltaTime)
{
    *this = *this + angularVelocity * *this * 0.5f * deltaTime;
}





std::ostream& operator<<(std::ostream& os, Quaternion q)
{
    char buffer[255];
    sprintf_s(buffer, "[%f  %f  %f  %f]\n",
        q[0], q[1], q[2],q[3]);
    os << buffer;
    return os;
}
