#ifndef VBO_H
#define VBO_H

#include <glew.h>
#include <glm.hpp>
#include <vector>

//Vertex Buffer Object = contient les donn�es des vertices
class VBO
{
public:
	//identifiant donn� par openGL
	GLuint ID;

	VBO(std::vector<GLfloat>& vertices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif