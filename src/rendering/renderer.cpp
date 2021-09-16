#include "renderer.h"
#include "sphere.h"

// modèle 3d de la pyramide avec les normales
GLfloat pyramidVertices[] =
{ // vertex (location 0)  / normales (location 1)
	-0.5f, 0.0f,  0.5f,	    0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,	    0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,	    0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 1.2f,  0.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 1.2f,  0.0f,     0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 1.2f,  0.0f,     0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 1.2f,  0.0f,     0.0f, 0.5f,  0.8f  // Facing side
};

//liste des triangles (chaque entier est l'id d'un vertex)
GLuint pyramidIndices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

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

	//debug
    printf("Version OpenGL: %s\nGPU: %s\nVersion GLEW: %s\n", glGetString(GL_VERSION), glGetString(GL_RENDERER), glewGetString(GLEW_VERSION));

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClearColor(0.172f, 0.184f, 0.2f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
	
	defaultShader = Shader("resources/default.vert", "resources/default.frag");

	//generation du Vertex Array Object, Vertex Buffer Object et Element Buffer Object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);


	printf("vertices : %d", s.vertices.size());
	printf("; indices : %d", s.indices.size());

	//ajout des vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, s.vertices.size() * sizeof(s.vertices), &(s.vertices[0]), GL_STATIC_DRAW);

	//ajout des indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, s.indices.size() * sizeof(s.indices), &(s.indices[0]), GL_STATIC_DRAW);

	//indique a OpenGL comment lires les données
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0); //vertices (location = 0)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1); //normales (location = 1)

	//lie le VBO, VAO et EBO à 0 pour ne pas les modifier accidentellement
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glEnable(GL_DEPTH_TEST);

    /*
    //Vsync
    if (SDL_GL_SetSwapInterval(1) < 0)
        printf("Impossible d'activer la synchronisation verticale ! Erreur SDL : %s\n", SDL_GetError());
    */
}

float t = 0;
void Renderer::Update(Scene scene)
{
    t += 0.01f;
    //float r = (1 + sin(t)) * 0.5f;
    //float g = (1 + sin(t*1.1f)) * 0.5f;
    //float b = (1 + sin(1+t*1.2f)) * 0.5f;
	//glClearColor(r, g, b, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(defaultShader.program);

	//transformations de la caméra avec des matrices

	

	//position de la lumière
	glUniform3f(glGetUniformLocation(defaultShader.program, "lightPos"), 2, 2, 2);

	//affiche les gameobjects
	glBindVertexArray(VAO);
	for (int i = 0; i < scene.GetObjectsCount(); i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		Vector3D* pos = scene.gameObjects[i].GetPosition();
		model = glm::translate(model, glm::vec3(pos->x, pos->y, pos->z));
		//model = glm::rotate(model, glm::radians(t * (i+1) * 50), glm::vec3(0, 1.0f, 0));
		
		view = glm::translate(view, glm::vec3(0, -0.5f, -3.0f));
		//view = glm::rotate(view, glm::radians(30.0f), glm::vec3(1.0f, 0, 0));
		proj = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(defaultShader.program, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(defaultShader.program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(defaultShader.program, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		glDrawElements(GL_TRIANGLES, s.indices.size(), GL_UNSIGNED_INT, 0);
	}
}