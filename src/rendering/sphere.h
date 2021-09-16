#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glew.h>

class Sphere
{
public:
	Sphere(float radius, int rows, int columns);
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLuint> indices;
};
#endif

