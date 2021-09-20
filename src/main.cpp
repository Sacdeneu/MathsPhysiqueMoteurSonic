#include <SDL.h>
#include <stdio.h>
#include <stdlib.h> 
#include "rendering/renderer.h"
#include "rendering/scene.h"
#include "Physics/Vector3D.h"

bool runGame = true;

void CreateParticle(Scene* scene, float velX, float velY)
{
	// Création des particles
	//std::shared_ptr<Particle> p = std::make_shared<Particle>(Particle(Vector3D(-5, 1, -5), 1));
	float randZ = (-10 + rand() % 20) * 0.2f;
	Particle* p = new Particle(Vector3D(-5, 1, -5), 1);
	scene->AddParticle(p);
	// Trajectoire de la particule
	p->SetVelocity(Vector3D(velX, velY, randZ));
	// La seule force est la force gravitationelle
	p->SetAcceleration(Vector3D(0, -9.81f, 0));
}

bool mouseButtonDown = false;
int HandleInputs(Scene* scene, Renderer* renderer)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: //ferme le jeu quand on ferme la fenetre
			runGame = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				int pixelMouseX, pixelMouseY;
				SDL_GetMouseState(&pixelMouseX, &pixelMouseY);
				float mouseX = pixelMouseX * 1.0f / SCREEN_WIDTH;
				float mouseY = 1 - (pixelMouseY * 1.0f / SCREEN_HEIGHT);
				CreateParticle(scene, mouseX * 15, mouseY * 15);
			}
			else
				renderer->camera.UpdateKeyboardInput(event.key.keysym.sym, true);
			break;

		case SDL_KEYUP:
			renderer->camera.UpdateKeyboardInput(event.key.keysym.sym, false);
			break;

		case SDL_MOUSEMOTION:
			if(mouseButtonDown)
				renderer->camera.UpdateMouseInput(event.motion.xrel, event.motion.yrel);
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
				mouseButtonDown = true;
			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
				mouseButtonDown = false;
			break;

		default:
			break;
		}
	}
	return 1;
}


int main( int argc, char* args[])
{
	//initialisation
	SDL_Window* window = NULL;
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Erreur de l'initalisation de SDL : %s\n", SDL_GetError());
	}
	else
	{
		//création de la fenêtre
		window = SDL_CreateWindow("Sonic Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
		if(window == NULL)
		{
			printf("Erreur de création de la fenêtre ! SDL_Error: %s\n", SDL_GetError() );
		}
		else //si la fenêtre a été crée
		{
			Renderer* renderer = new Renderer(window);
			Scene* scene = new Scene();

			Particle* p1 = new Particle(Vector3D(-5, 1, -5), 1);
			scene->AddParticle(p1);

			Uint64 lastUpdate = SDL_GetPerformanceCounter();

			//boucle de jeu
			while (runGame)
			{
				//calcul de dt
				Uint64 now = SDL_GetPerformanceCounter();
				float deltaTime = ((now - lastUpdate) / (float)SDL_GetPerformanceFrequency());
				lastUpdate = now;

				//mise à jour des entrées
				HandleInputs(scene, renderer);

				//mise à jour de la physique et de la logique
				scene->Update(deltaTime);
				renderer->camera.Update(deltaTime);

				//mise à jour de l'affichage
				renderer->Update(scene);
				SDL_GL_SwapWindow(window);

				//rendu à 60FPS
				SDL_Delay(1000 / 60);
			}
		}
	}

	Vector3D vector1 = Vector3D(1, 2, 3);
	Vector3D vector2 = Vector3D(4, 5, 6);
	Vector3D vector3 = vector1 + vector2;
	Vector3D vector4 = vector1 - vector2;
	std::cout << "Norm " << vector1.Norm(vector1.x, vector1.y, vector1.z) << std::endl;
	std::cout << "NormSquare " << vector1.NormSquare(vector1.Norm(vector1.x, vector1.y, vector1.z)) << std::endl;
	std::cout << "NormSquare 2 " << vector1.NormSquare(vector1) << std::endl;
	std::cout << "Normalisation " << vector1.Normalisation(vector1.Norm(vector1.x, vector1.y, vector1.z), vector1) << std::endl;
	std::cout << "ScalarMultiply " << vector1.ScalarMultiply(5.0, vector1) << std::endl;
	std::cout << "Addition " << vector1.Addition(vector1, vector2) << std::endl;
	std::cout << "Substraction " << vector1.Substraction(vector1, vector2) << std::endl;
	std::cout << "Multiply " << vector1.Multiply(vector1, vector2) << std::endl;
	std::cout << "ScalarProduct " << vector1.ScalarProduct(vector1, vector2) << std::endl;
	std::cout << "CrossProduct " <<vector1.CrossProduct(vector1, vector2) << std::endl;
	std::cout << "Vector3 Addition " << vector3 << std::endl;
	std::cout << "Vector4 Substraction " << vector4 << std::endl;





	//destruction de la fenêtre
	SDL_DestroyWindow(window);
	SDL_Quit();


	return 0;
}