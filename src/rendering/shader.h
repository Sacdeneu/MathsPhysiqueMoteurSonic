#ifndef SHADER_H
#define SHADER_H

#include <glew.h>
#include <SDL_opengl.h>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

class Shader
{
public:
	//id du shader program
	GLuint program;
	Shader();
	Shader(const char* vertexFile, const char* fragmentFile);
	void compileErrors(unsigned int shader, const char* type);
};
#endif

