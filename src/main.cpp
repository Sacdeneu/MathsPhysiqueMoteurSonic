#include <SDL.h>
#include <stdio.h>
#include <stdlib.h> 
#include "rendering/renderer.h"
#include "rendering/scene.h"
#include "math/Vector3D.h"
#include "Physics/forcesRegister.h"
#include "Physics/rigidbodyGravityGenerator.h"
#include "Physics/rigidbodyDampingGenerator.h"
#include "Physics/rigidbodyAnchoredSpringGenerator.h"
#include "Physics/rigidbodySpringGenerator.h"
#include "Physics/rigidbodyBungeeGenerator.h"
#include "Physics/rigidbodyArchimedeGenerator.h"

#include "Physics/rigidbodyContactSolver.h"
#include "Physics/rigidbodyCable.h"
#include "Physics/rigidbodyRod.h"

#include "math/Matrix4.h"
#include "math/Matrix3.h"

#include "math/Quaternion.h"

#include "physics/primitive.h";
#include "physics/box.h";

bool runGame = true;
float rigidbodyMass = 1;
float randomZDirection = 2.5f;
float rigidbodyLinkLength = 2;

ForcesRegister forcesRegister;
RigidbodyContactSolver contactSolver;

//############################
//#                          #
//#  CREATION DE RIGIBDODY   #
//#                          #
//############################


// Création d'un rigidbody selon les paramètres gérés par la fenêtre ImGUI.
// Le rigidbody créé est soumis à la gravité et au damping.
Rigidbody* CreateRigidbody(Scene* scene, Vector3D pos, Vector3D velocity = Vector3D(0, 0, 0), float massFactor = 1)
{
	Rigidbody* p = new Rigidbody(pos, rigidbodyMass * massFactor);
	scene->Addrigidbody(p);
	p->SetVelocity(velocity);
	p->AddForceAtPoint(Vector3D(0, 1, 0), Vector3D(velocity.x * 50, 0, velocity.z * 50));

	forcesRegister.AddEntry(p, new RigidbodyGravityGenerator());
	forcesRegister.AddEntry(p, new RigidbodyDampingGenerator());

	p->AddPrimitive(new Box(Vector3D(0.8f, 0.5f, 0.5f)));
	p->AddPrimitive(new Box(Vector3D(1.1f, -0.2f, 0), Vector3D(0.3f, 0.3f, 0.5f)));
	p->AddPrimitive(new Box(Vector3D(-0.9f, -0.2f, 0), Vector3D(0.1f, 0.3f, 0.5f)));
	p->AddPrimitive(new Box(Vector3D(-0.6f, -0.35f, 0.6f), Vector3D(0.2f, 0.2f, 0.1f)));
	p->AddPrimitive(new Box(Vector3D(0.7f, -0.35f, 0.6f), Vector3D(0.2f, 0.2f, 0.1f)));
	p->AddPrimitive(new Box(Vector3D(-0.6f, -0.35f, -0.6f), Vector3D(0.2f, 0.2f, 0.1f)));
	p->AddPrimitive(new Box(Vector3D(0.7f, -0.35f, -0.6f), Vector3D(0.2f, 0.2f, 0.1f)));

	return p;
}

//##########
//#        #
//#  MAIN  #
//#        #
//##########

//supprime tous les éléments de la scène
void ResetScene(Scene* scene)
{
	contactSolver.generator.RemoveAllrigidbodyLink();
	for (int i = Scene::mainScene->gameObjects.size() - 1; i >= 0; i--)
	{
		Scene::mainScene->RemoveRigidbody(Scene::mainScene->gameObjects[i]);
	}
}

bool mouseButtonDown = false;
// Gère les inputs pour déplacer la caméra et faire spawn des objets.
int HandleInputs(Renderer* renderer)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT: //ferme le jeu quand on ferme la fenêtre
			runGame = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_SPACE && !Scene::mainScene->isPaused) // Fait spawn un rigidbody en fonction de la position de la souris
			{
				int pixelMouseX, pixelMouseY;
				SDL_GetMouseState(&pixelMouseX, &pixelMouseY);
				float mouseX = pixelMouseX * 1.0f / SCREEN_WIDTH;
				float mouseY = 1 - (pixelMouseY * 1.0f / SCREEN_HEIGHT);
				float randZ = (-100 + rand() % 200) * randomZDirection * 0.01f;
				CreateRigidbody(Scene::mainScene, Vector3D(0, 1, 0), Vector3D(-10 + mouseX * 20, mouseY * 15, randZ));
			}
			else
			{
				// Update les déplacements caméra et blob
				renderer->camera.UpdateKeyboardInput(event.key.keysym.sym, true);
			}
			break;

		case SDL_KEYUP: // Update les déplacements caméra et blob pour qu'ils s'arrêtent
			renderer->camera.UpdateKeyboardInput(event.key.keysym.sym, false);
			break;

		case SDL_MOUSEMOTION: // Rotate la caméra si le clic souris est maintenu.
			if(mouseButtonDown)
				renderer->camera.UpdateMouseInput(event.motion.xrel, event.motion.yrel);
			break;

		case SDL_MOUSEBUTTONDOWN: // clic souris maintenu
			if (event.button.button == SDL_BUTTON_RIGHT)
				mouseButtonDown = true;
			break;

		case SDL_MOUSEBUTTONUP: // clic souris relaché
			if (event.button.button == SDL_BUTTON_RIGHT)
				mouseButtonDown = false;
			break;

		default:
			break;
		}
	}
	return 1;
}

//création de la fenetre graphique
// contient principalement des fonctions debug / tests
void MakeImGuiWindow(float physicsUpdateTime)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(0, 0));
	ImGui::SetWindowPos(ImVec2(20, 20));

	ImGui::Text("Rigidbodies dans la scene: %d", Scene::mainScene->GetObjectsCount());
	ImGui::Text("Mise a jour de la physique: %.5fms", physicsUpdateTime);
	ImGui::Dummy(ImVec2(0.0f, 20.0f));
	ImGui::PushItemWidth(150);
	ImGui::SliderFloat("Masse des rigidbodys", &rigidbodyMass, 0.1, 10, "%.2f");
	ImGui::SliderFloat("Dispersion Z", &randomZDirection, 0, 5, "%.1f");

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui::StyleColorsDark();

			// initialisation du renderer et de la scène
			Renderer* renderer = new Renderer(window);
			Scene::mainScene = new Scene(&forcesRegister);

			Uint64 lastUpdate = SDL_GetPerformanceCounter();

			//boucle de jeu
			while (runGame)
			{
				//mise à jour des entrées
				HandleInputs(renderer);

				//calcul de dt
				Uint64 now = SDL_GetPerformanceCounter();
				float deltaTime = ((now - lastUpdate) / (float)SDL_GetPerformanceFrequency());
				lastUpdate = now;

				//mise à jour de la physique et de la logique
				if (!Scene::mainScene->isPaused)
				{
					forcesRegister.Update(deltaTime);
					Scene::mainScene->Update(deltaTime);

					//test collisions
					contactSolver.UpdateCollisions(Scene::mainScene, 4);
				}
				
				float physicsUpdateTime = ((SDL_GetPerformanceCounter() - lastUpdate) / (float)SDL_GetPerformanceFrequency()) * 1000;

				renderer->camera.Update(deltaTime);

				//mise à jour de l'affichage
				renderer->Update(Scene::mainScene);
				renderer->DrawOctree(contactSolver.generator.octree);
				MakeImGuiWindow(physicsUpdateTime);
				SDL_GL_SwapWindow(window);

				//rendu à 60FPS
				SDL_Delay(1000 / 60);
			}
			
			delete renderer;
			delete Scene::mainScene;
		}
	}

	//destruction de la fenêtre
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}