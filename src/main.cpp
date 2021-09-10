#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main( int argc, char* args[])
{
	//initialisation
	SDL_Window* window = NULL;
	if(SDL_Init( SDL_INIT_VIDEO) < 0)
	{
		printf("Erreur de l'initalisation de SDL : %s\n", SDL_GetError());
	}
	else
	{
		//création de la fenêtre
		window = SDL_CreateWindow("Sonic Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window == NULL)
		{
			printf("Erreur de création de la fenêtre ! SDL_Error: %s\n", SDL_GetError() );
		}
		else //cas ou la fenetre fonctionne
		{
			//couleur de fond
			SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x23, 0x27, 0x2A));

			SDL_UpdateWindowSurface(window);
			
			//boucle de jeu
			bool close = false;
			while (!close)
			{
				//gestion des événements
				SDL_Event event;
				while (SDL_PollEvent(&event))
				{
					switch (event.type)
					{
					case SDL_QUIT:
						close = true;
						break;

					case SDL_KEYDOWN:
						printf("Detection d'une touche\n");
						break;

					default:
						break;
					}
				}
			}

			//rendu à 60FPS
			SDL_Delay( 1.0 / 60 );
		}
	}

	//destruction de la fenêtre
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}