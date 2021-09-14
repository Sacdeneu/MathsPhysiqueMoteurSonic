#include "shader.h"

#include <iostream>
#include <filesystem>
#include <stdio.h>
#include <limits.h>

//lit le contenu d'un fichier
std::string get_file_contents(const char* filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (file.is_open())
	{
		std::string content;
		file.seekg(0, std::ios::end);
		content.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&content[0], content.size());
		file.close();
		return(content);
	}
	else
	{
		std::cout << "Impossible d'ouvrir le fichier de shader " << filename << std::endl;
		exit(0);
	}
		
}

Shader::Shader()
{
}

//initialiser le shader a partir des deux programmes
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//lecture des fichiers
	std::string vertexCodeStr = get_file_contents(vertexFile);
	std::string fragmentCodeStr = get_file_contents(fragmentFile);
	const char* vertexCode = vertexCodeStr.c_str();
	const char* fragmentCode = fragmentCodeStr.c_str();

	//création du vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	//création du fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	glCompileShader(fragmentShader);
	compileErrors(vertexShader, "FRAGMENT");

	//création du shader program et liens
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	compileErrors(vertexShader, "PROGRAM");

	//on peut supprimer les deux shaders une fois le programme créé
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}