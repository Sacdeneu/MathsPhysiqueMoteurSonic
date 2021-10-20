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
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

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
	Shader defaultShader, gridShader, mapShader;
	VAO sphereVAO, gridVAO, cubeVAO;
	std::vector<GLfloat> gridVertices;
	std::vector<GLuint> gridIndices;
	std::vector<GLfloat> cubeVertices;
	std::vector<GLuint> cubeIndices;
};

#endif

