#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <stdio.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h> 
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "shader.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Renderer
{
public:
	Renderer(SDL_Window* targetWindow);
	void Update();
private:
	SDL_GLContext context;
	Shader defaultShader;
	GLuint VAO, VBO, EBO;
};

#endif

