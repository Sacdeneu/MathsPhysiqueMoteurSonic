#include <SDL.h>
#include <stdio.h>
#include "rendering/renderer.h"
#include "../Vector3D.h"


bool runGame = true;

int handleInputs()
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
			printf("Detection d'une touche\n");
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
			Renderer renderer = Renderer(window);

			//boucle de jeu
			while (runGame)
			{
				handleInputs();
				renderer.Update();
				SDL_GL_SwapWindow(window);

				//rendu à 60FPS
				SDL_Delay(1000 / 60);
			}
		}
	}

	Vector3D vector1 = Vector3D(1, 2, 3);
	Vector3D vector2 = Vector3D(4, 5, 6);
	std::cout << "Norm " << vector1.Norm(vector1.x, vector1.y, vector1.z) << std::endl;
	std::cout << "NormSquare " << vector1.NormSquare(vector1.Norm(vector1.x, vector1.y, vector1.z)) << std::endl;
	std::cout << "Normalisation " << vector1.Normalisation(vector1.Norm(vector1.x, vector1.y, vector1.z), vector1) << std::endl;
	std::cout << "ScalarMultiply " << vector1.ScalarMultiply(5.0, vector1) << std::endl;
	std::cout << "Addition " << vector1.Addition(vector1, vector2) << std::endl;
	std::cout << "Substraction " << vector1.Substraction(vector1, vector2) << std::endl;
	std::cout << "Multiply " << vector1.Multiply(vector1, vector2) << std::endl;
	std::cout << "ScalarProduct " << vector1.ScalarProduct(vector1, vector2) << std::endl;
	std::cout << "CrossProduct " <<vector1.CrossProduct(vector1, vector2) << std::endl;



	//destruction de la fenêtre
	SDL_DestroyWindow(window);
	SDL_Quit();


	return 0;
}