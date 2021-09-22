#ifndef VBO_H
#define VBO_H

#include <glew.h>
#include <glm.hpp>
#include <vector>

//Vertex Buffer Object = contient les données des vertices
class VBO
{
public:
	//identifiant donné par openGL
	GLuint ID;

	VBO(std::vector<GLfloat>& vertices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif