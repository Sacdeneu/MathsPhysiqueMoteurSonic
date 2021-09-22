#ifndef VAO_H
#define VAO_H

#include <glew.h>
#include "VBO.h"

//Vertex Array Object = fait le lien entre les données du VBO
class VAO
{
public:
	//identifiant donné par openGL
	GLuint ID;

	VAO();

	void Init();
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};

#endif