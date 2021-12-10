#include "renderer.h"
#include "sphere.h"
#include <stb_image.h>

Sphere s(1.0f, 24, 24);

void LoadTexture(const char* filename, GLuint* texture)
{
	int textureWidth, textureHeight, channelCount;
	unsigned char* bytes = stbi_load(filename, &textureWidth, &textureHeight, &channelCount, 0);
	glGenTextures(1, texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//constructeur
Renderer::Renderer(SDL_Window* targetWindow)
{
	//cr�ation du contexte
    context = SDL_GL_CreateContext(targetWindow);
    if (context == NULL)
    {
        printf("Le contexte OpenGL n'a pas pu �tre cr��! Erreur SDL : %s\n", SDL_GetError());
		exit(0);
    }

	//initialisation de glew
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Impossible d'initialiser GLEW. Erreur : %s\n", glewGetErrorString(err));
		exit(0);
	}

	//d�fini le set fonctions opengl � utiliser
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	ImGui_ImplSDL2_InitForOpenGL(targetWindow, context);
	ImGui_ImplOpenGL3_Init("#version 330");

	//debug
    printf("Version OpenGL: %s\nGPU: %s\nVersion GLEW: %s\n", glGetString(GL_VERSION), glGetString(GL_RENDERER), glewGetString(GLEW_VERSION));

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	//glClearColor(0.172f, 0.184f, 0.2f, 0.0f);
	glClearColor(0.30f, 0.74f, 1, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
	
	//g�n�ration des shaders
	defaultShader = Shader("resources/default.vert", "resources/default.frag");
	gridShader = Shader("resources/grid.vert", "resources/grid.frag");
	mapShader = Shader("resources/map.vert", "resources/map.frag");

	//g�n�ration du VAO de la sph�re
	sphereVAO.Init();
	sphereVAO.Bind();
	VBO sphereVBO(s.vertices);
	EBO sphereEBO(s.indices);

	// vertex (location = 0)
	sphereVAO.LinkAttrib(sphereVBO, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	// normal (location = 1)
	sphereVAO.LinkAttrib(sphereVBO, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	//unbind des liens pour ne pas les laisser actifs lors des assignations suivantes
	sphereVAO.Unbind();
	sphereVBO.Unbind();
	sphereEBO.Unbind();

	glEnable(GL_DEPTH_TEST);
	camera.SetPosition(0, 3, 15);

	//g�n�ration de la grille
	int minGrid = -20;
	int maxGrid = 20;
	for (int i = minGrid; i <= maxGrid; i++)
	{
		gridVertices.push_back(minGrid);
		gridVertices.push_back(i);
		gridVertices.push_back(0);

		gridVertices.push_back(maxGrid);
		gridVertices.push_back(i);
		gridVertices.push_back(0);

		gridVertices.push_back(i);
		gridVertices.push_back(minGrid);
		gridVertices.push_back(0);

		gridVertices.push_back(i);
		gridVertices.push_back(maxGrid);
		gridVertices.push_back(0);
	}

	//VAO de la grille
	gridVAO.Init();
	gridVAO.Bind();
	VBO gridVBO(gridVertices);
	gridVAO.LinkAttrib(gridVBO, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);
	gridVAO.Unbind();
	gridVBO.Unbind();

	cubeVertices = {
		.5f,.5f,.5f,0,1,0,    .5f,.5f,-.5f,0,1,0,    -.5f,.5f,-.5f,0,1,0,    -.5f,.5f,.5f,0,1,0,   //top
		.5f,-.5f,.5f,0,-1,0,  .5f,-.5f,-.5f,0,-1,0,  -.5f,-.5f,-.5f,0,-1,0,  -.5f,-.5f,.5f,0,-1,0, //bottom
		.5f,.5f,-.5f,0,0,1,   .5f,-.5f,-.5f,0,0,1,   -.5f,-.5f,-.5f,0,0,1,   -.5f,.5f,-.5f,0,0,1,  //front
		.5f,.5f,.5f,0,0,-1,   .5f,-.5f,.5f,0,0,-1,   -.5f,-.5f,.5f,0,0,-1,   -.5f,.5f,.5f,0,0,-1,  //back
		-.5f,.5f,.5f,-1,0,0,  -.5f,-.5f,.5f,-1,0,0,  -.5f,-.5f,-.5f,-1,0,0,  -.5f,.5f,-.5f,-1,0,0, //left
		.5f,.5f,.5f,1,0,0,    .5f,-.5f,.5f,1,0,0,    .5f,-.5f,-.5f,1,0,0,    .5f,.5f,-.5f,1,0,0    //right
	};

	cubeIndices = {
		0,1,2,0,2,3,
		4,5,6,4,6,7,
		8,9,10,8,10,11,
		12,13,14,12,14,15,
		16,17,18,16,18,19,
		20,21,22,20,22,23
	};

	cubeVAO.Init();
	cubeVAO.Bind();
	VBO cubeVBO(cubeVertices);
	EBO cubeEBO(cubeIndices);
	cubeVAO.LinkAttrib(cubeVBO, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	cubeVAO.LinkAttrib(cubeVBO, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	cubeVAO.Unbind();
	cubeVBO.Unbind();
	cubeEBO.Unbind();

	planeVertices = { 1000,0,1000,0,1,0,    1000,0,-1000,0,1,0,    -1000,0,-1000,0,1,0,    -1000,0,1000,0,1,0 };
	planeIndices = { 0,1,2,0,2,3 };

	planeVAO.Init();
	planeVAO.Bind();
	VBO planeVBO(planeVertices);
	EBO planeEBO(planeIndices);
	planeVAO.LinkAttrib(planeVBO, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	planeVAO.LinkAttrib(planeVBO, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	planeVAO.Unbind();
	planeVBO.Unbind();
	planeEBO.Unbind();

	LoadTexture("resources/grass.png", &grassTexture);
	LoadTexture("resources/dirt.png", &dirtTexture);
}

float t = 0;
void Renderer::Update(Scene* scene)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(defaultShader.program);

	//transformations de la cam�ra
	glm::vec3 viewPos = camera.position;
	camera.SetMatrix(60, 0.1f, 500.0f, defaultShader, "cameraMatrix");

	//position de la lumi�re
	glUniform3f(glGetUniformLocation(defaultShader.program, "lightDir"), -0.8f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(defaultShader.program, "viewPos"), viewPos.x, viewPos.y, viewPos.z);

	for (int i = 0; i < scene->GetObjectsCount(); i++)
	{
		Rigidbody* obj = scene->gameObjects[i];
		for (int j = 0; j < obj->GetPrimitiveCount(); j++)
		{
			Primitive* primitive = obj->GetPrimitive(j);
			int modelLoc = glGetUniformLocation(defaultShader.program, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, primitive->GetTransform().GetGLMatrix());

			if (primitive->type == PrimitiveType::box)
			{
				cubeVAO.Bind();
				glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, 0);
				cubeVAO.Unbind();
			}
			else if(primitive->type == PrimitiveType::plane)
			{
				planeVAO.Bind();
				glDrawElements(GL_TRIANGLES, planeIndices.size(), GL_UNSIGNED_INT, 0);
				planeVAO.Unbind();
			}
		}
	}
	//sphereVAO.Unbind();

	//if(scene->GetObjectsCount() > 0)
	//std::cout << scene->gameObjects[0]->transformMatrix.GetGLMatrix() << std::endl;

	//affiche la map
	glUseProgram(mapShader.program);
	glUniform3f(glGetUniformLocation(mapShader.program, "lightDir"), -0.8f, -1.0f, 0.3f);
	glUniform1i(glGetUniformLocation(mapShader.program, "mainTex"), 0);
	
	camera.SetMatrix(60, 0.1f, 500.0f, mapShader, "cameraMatrix");
	cubeVAO.Bind();
	for (int i = 0; i < scene->map.size(); i++)
	{
		glm::mat4 model = glm::mat4(1.0f);

		Vector3D pos = scene->map[i].GetPosition();
		Vector3D scale = scene->map[i].GetScale();
		model = glm::translate(model, glm::vec3(pos.x, pos.y, pos.z));
		model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));

		int modelLoc = glGetUniformLocation(mapShader.program, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glBindTexture(GL_TEXTURE_2D, scene->map[i].GetTextureID() != 0 ? grassTexture : dirtTexture);

		glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, 0);
	}
	cubeVAO.Unbind();

	/*
	//affichage de la grille
	glUseProgram(gridShader.program);
	camera.SetMatrix(60, 0.1f, 500.0f, gridShader, "cameraMatrix");
	gridVAO.Bind();
	glm::mat4 model = glm::mat4(1.0f);
	int modelLoc = glGetUniformLocation(gridShader.program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_LINES, 0, gridVertices.size() / 3);
	*/
}