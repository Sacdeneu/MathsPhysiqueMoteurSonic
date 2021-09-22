#ifndef VAO_H
#define VAO_H

#include <glew.h>
#include "VBO.h"

//Vertex Array Object = fait le lien entre les donn�es du VBO
class VAO
{
public:
	//identifiant donn� par openGL
	GLuint ID;

	VAO();

	void Init();
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};

#endif