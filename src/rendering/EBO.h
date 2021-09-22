#ifndef EBO_H
#define EBO_H

#include <glew.h>
#include <vector>

//Elements Buffer Objet = contient les indices
class EBO
{
public:
	//identifiant donné par openGL
	GLuint ID;

	EBO(std::vector<GLuint>& indices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif