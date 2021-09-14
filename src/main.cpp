#include <SDL.h>
#include <stdio.h>
#include "rendering/renderer.h"

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

	//destruction de la fenêtre
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}