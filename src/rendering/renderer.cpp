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

	//transformations de la cam�ra
	glm::vec3 viewPos = camera.position;
	glm::mat4 cameraMatrix = camera.GetMatrix(60, 0.1f, 500.0f);

	for (int i = 0; i < scene->GetObjectsCount(); i++)
	{
		Rigidbody* obj = scene->gameObjects[i];

		//shader qui sera utilis� pour le rendu de ce rigidbody
		Shader rigidbodyShader;

		//on s�l�ctionne le bon shader en fonction du type
		switch(obj->renderingType)
		{
			case RenderingType::grass:
			case RenderingType::dirt:
				rigidbodyShader = mapShader;
				break;

			default: //RenderingType::blue
				rigidbodyShader = defaultShader;
				break;
		}

		//on active le shader s�l�ctionn� et on applique les uniform communs � tous (cam�ra et lum�re)
		glUseProgram(rigidbodyShader.program);
		glUniformMatrix4fv(glGetUniformLocation(rigidbodyShader.program, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
		glUniform3f(glGetUniformLocation(rigidbodyShader.program, "lightDir"), -0.8f, -1.0f, 0.3f);

		//on applique les uniform sp�cifique � chaque type de rendu
		switch (obj->renderingType)
		{
		case RenderingType::grass:
			glUniform1i(glGetUniformLocation(rigidbodyShader.program, "mainTex"), 0);
			glBindTexture(GL_TEXTURE_2D, grassTexture);
			break;

		case RenderingType::dirt:
			glUniform1i(glGetUniformLocation(rigidbodyShader.program, "mainTex"), 0);
			glBindTexture(GL_TEXTURE_2D, dirtTexture);
			break;

		default: //RenderingType::blue
			glUniform3f(glGetUniformLocation(rigidbodyShader.program, "viewPos"), viewPos.x, viewPos.y, viewPos.z);
			break;
		}
		
		//on affiche chaque primitive de ce rigidbody
		for (int j = 0; j < obj->GetPrimitiveCount(); j++)
		{
			Primitive* primitive = obj->GetPrimitive(j);

			//on change la matrice model pour afficher la primitive au bon endroit
			glUniformMatrix4fv(glGetUniformLocation(rigidbodyShader.program, "model"), 1, GL_FALSE, primitive->GetTransform().GetGLMatrix());

			//on active un VAO diff�rent en fonction du type de la primitive
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
}

// Affiche l'octree dans la scene
void Renderer::DrawOctree(Octree& octree)
{
	std::vector<Rect> listBounds;
	octree.GetAllBounds(listBounds);
	gridVertices.clear();

	for (size_t i = 0; i < listBounds.size(); i++)
	{
		Rect rect = listBounds[i];

		Vector3D regionCorners[] =
		{
			Vector3D(rect.position.x - rect.scale.x, rect.position.y - rect.scale.y, rect.position.z - rect.scale.z),
			Vector3D(rect.position.x + rect.scale.x, rect.position.y - rect.scale.y, rect.position.z - rect.scale.z),
			Vector3D(rect.position.x + rect.scale.x, rect.position.y + rect.scale.y, rect.position.z - rect.scale.z),
			Vector3D(rect.position.x - rect.scale.x, rect.position.y + rect.scale.y, rect.position.z - rect.scale.z),
			Vector3D(rect.position.x - rect.scale.x, rect.position.y - rect.scale.y, rect.position.z + rect.scale.z),
			Vector3D(rect.position.x + rect.scale.x, rect.position.y - rect.scale.y, rect.position.z + rect.scale.z),
			Vector3D(rect.position.x + rect.scale.x, rect.position.y + rect.scale.y, rect.position.z + rect.scale.z),
			Vector3D(rect.position.x - rect.scale.x, rect.position.y + rect.scale.y, rect.position.z + rect.scale.z)
		};

		AddLineToGrid(&regionCorners[0], &regionCorners[1]);
		AddLineToGrid(&regionCorners[1], &regionCorners[2]);
		AddLineToGrid(&regionCorners[2], &regionCorners[3]);
		AddLineToGrid(&regionCorners[3], &regionCorners[0]);
		AddLineToGrid(&regionCorners[4], &regionCorners[5]);
		AddLineToGrid(&regionCorners[5], &regionCorners[6]);
		AddLineToGrid(&regionCorners[6], &regionCorners[7]);
		AddLineToGrid(&regionCorners[7], &regionCorners[4]);
		AddLineToGrid(&regionCorners[0], &regionCorners[4]);
		AddLineToGrid(&regionCorners[1], &regionCorners[5]);
		AddLineToGrid(&regionCorners[2], &regionCorners[6]);
		AddLineToGrid(&regionCorners[3], &regionCorners[7]);
	}

	//VAO de la grille
	gridVAO.Bind();
	VBO gridVBO(gridVertices);
	gridVAO.LinkAttrib(gridVBO, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);
	gridVBO.Unbind();

	glUseProgram(gridShader.program);
	glm::mat4 cameraMatrix = camera.GetMatrix(60, 0.1f, 500.0f);
	glUniformMatrix4fv(glGetUniformLocation(gridShader.program, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
	gridVAO.Bind();
	glDrawArrays(GL_LINES, 0, gridVertices.size() / 3);
	gridVAO.Unbind();
}

void Renderer::AddLineToGrid(Vector3D* pointA, Vector3D* pointB)
{
	gridVertices.insert(gridVertices.end(), { pointA->x, pointA->y, pointA->z, pointB->x, pointB->y, pointB->z });
}