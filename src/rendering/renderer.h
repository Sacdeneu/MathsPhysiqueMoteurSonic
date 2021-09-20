#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <stdio.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <math.h> 
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "camera.h"
#include "shader.h"
#include "scene.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Renderer
{
public:
	Renderer(SDL_Window* targetWindow);
	Camera camera;
	void Update(Scene* scene);
private:
	SDL_GLContext context;
	Shader defaultShader;
	GLuint VAO, VBO, EBO;
};

#endif

