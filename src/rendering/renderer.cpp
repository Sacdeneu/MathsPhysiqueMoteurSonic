#include "renderer.h"
#include "sphere.h"

Sphere s(0.5f, 24, 24);

//constructeur
Renderer::Renderer(SDL_Window* targetWindow)
{
	//création du contexte
    context = SDL_GL_CreateContext(targetWindow);
    if (context == NULL)
    {
        printf("Le contexte OpenGL n'a pas pu être créé! Erreur SDL : %s\n", SDL_GetError());
		exit(0);
    }

	//initialisation de glew
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Impossible d'initialiser GLEW. Erreur : %s\n", glewGetErrorString(err));
		exit(0);
	}

	//défini le set fonctions opengl à utiliser
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	ImGui_ImplSDL2_InitForOpenGL(targetWindow, context);
	ImGui_ImplOpenGL3_Init("#version 330");

	//debug
    printf("Version OpenGL: %s\nGPU: %s\nVersion GLEW: %s\n", glGetString(GL_VERSION), glGetString(GL_RENDERER), glewGetString(GLEW_VERSION));

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClearColor(0.172f, 0.184f, 0.2f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
	
	//génération des shaders
	defaultShader = Shader("resources/default.vert", "resources/default.frag");
	gridShader = Shader("resources/grid.vert", "resources/grid.frag");

	//génération du VAO de la sphère
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

	//génération de la grille
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
}

float t = 0;
void Renderer::Update(Scene* scene)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(defaultShader.program);

	//transformations de la caméra
	glm::vec3 viewPos = camera.position;
	camera.SetMatrix(60, 0.1f, 500.0f, defaultShader, "cameraMatrix");

	//position de la lumière
	glUniform3f(glGetUniformLocation(defaultShader.program, "lightDir"), -0.8f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(defaultShader.program, "viewPos"), viewPos.x, viewPos.y, viewPos.z);

	//affiche les particules
	sphereVAO.Bind();
	for (int i = 0; i < scene->GetObjectsCount(); i++)
	{
		glm::mat4 model = glm::mat4(1.0f);

		Vector3D pos = scene->gameObjects[i]->GetPosition();
		model = glm::translate(model, glm::vec3(pos.x, pos.y, pos.z));
		//model = glm::rotate(model, glm::radians(t * (i+1) * 50), glm::vec3(0, 1.0f, 0));

		float radius = cbrt(scene->gameObjects[i]->GetMass());
		model = glm::scale(model, glm::vec3(radius, radius, radius));

		int modelLoc = glGetUniformLocation(defaultShader.program, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawElements(GL_TRIANGLES, s.indices.size(), GL_UNSIGNED_INT, 0);
	}

	//affichage de la grille
	glUseProgram(gridShader.program);
	camera.SetMatrix(60, 0.1f, 500.0f, gridShader, "cameraMatrix");
	gridVAO.Bind();
	glm::mat4 model = glm::mat4(1.0f);
	int modelLoc = glGetUniformLocation(gridShader.program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_LINES, 0, gridVertices.size() / 3);
}