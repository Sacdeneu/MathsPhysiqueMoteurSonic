#include <SDL.h>
#include <stdio.h>
#include <stdlib.h> 
#include "rendering/renderer.h"
#include "rendering/scene.h"
#include "Physics/Vector3D.h"
#include "Physics/forcesRegister.h"
#include "Physics/particleGravityGenerator.h"
#include "Physics/particleDampingGenerator.h"
#include "Physics/particleAnchoredSpringGenerator.h"
#include "Physics/particleSpringGenerator.h"

#include "Physics/ParticleContactSolver.h"
#include "Physics/ParticleCable.h"
#include "Physics/ParticleRod.h"

bool runGame = true;
float particleMass = 1;
float randomZDirection = 0;// 2.5f;
ForcesRegister forcesRegister;

void CreateParticle(Scene* scene, float velX, float velY)
{
	// Création des particles
	//std::shared_ptr<Particle> p = std::make_shared<Particle>(Particle(Vector3D(-5, 1, -5), 1));
	float randZ = (-100 + rand() % 200) * randomZDirection * 0.01f;
	Particle* p = new Particle(Vector3D(0, 2, 0), particleMass);
	scene->AddParticle(p);
	// Trajectoire de la particule
	p->SetVelocity(Vector3D(velX, velY, randZ));
	// Les seules forces sont la force gravitationelle et le damping
	forcesRegister.AddEntry(p, new ParticleGravityGenerator());
	forcesRegister.AddEntry(p, new ParticleDampingGenerator());
	//forcesRegister.AddEntry(p, new ParticleAnchoredSpringGenerator());
}

void CreateSpring(Scene* scene)
{
	// Création des particles
	Particle* p1 = new Particle(Vector3D(-2, 2, 0), particleMass);
	scene->AddParticle(p1);
	Particle* p2 = new Particle(Vector3D(2, 2, 0), particleMass * 2);
	scene->AddParticle(p2);
	// Les seules forces sont la force gravitationelle et le damping
	forcesRegister.AddEntry(p1, new ParticleDampingGenerator());
	forcesRegister.AddEntry(p1, new ParticleSpringGenerator(p2));
	forcesRegister.AddEntry(p2, new ParticleDampingGenerator());
	forcesRegister.AddEntry(p2, new ParticleSpringGenerator(p1));
}

bool mouseButtonDown = false;
int HandleInputs(Renderer* renderer)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);

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
				CreateParticle(Scene::mainScene, -10 + mouseX * 20, mouseY * 15);
			}
			else if (event.key.keysym.sym == SDLK_r)
			{
				CreateSpring(Scene::mainScene);
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
			if (event.button.button == SDL_BUTTON_RIGHT)
				mouseButtonDown = true;
			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_RIGHT)
				mouseButtonDown = false;
			break;

		default:
			break;
		}
	}
	return 1;
}

void MakeImGuiWindow(float physicsUpdateTime)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(0, 0));
	ImGui::SetWindowPos(ImVec2(20, 20));

	ImGui::Text("Particules dans la scene: %d", Scene::mainScene->GetObjectsCount());
	ImGui::Text("Mise a jour de la physique: %.5fms", physicsUpdateTime);
	ImGui::Dummy(ImVec2(0.0f, 20.0f));
	ImGui::PushItemWidth(150);
	ImGui::SliderFloat("Masse des particules", &particleMass, 0.1, 10, "%.2f");
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

			Renderer* renderer = new Renderer(window);
			Scene::mainScene = new Scene(&forcesRegister);

			// Collision + particles de tests
			ParticleContactSolver* particleContactSolver = new ParticleContactSolver();
			CreateParticle(Scene::mainScene, 0, 5);
			CreateParticle(Scene::mainScene, -5, 7);
			ParticleCable* cable = new ParticleCable(Scene::mainScene->gameObjects[0],
													 Scene::mainScene->gameObjects[1], 2);
			particleContactSolver->AddParticleLink(cable);

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
				forcesRegister.Update(deltaTime);
				Scene::mainScene->Update(deltaTime);
				
				//test collisions
				particleContactSolver->UpdateCollisions(Scene::mainScene, 4);
				float physicsUpdateTime = ((SDL_GetPerformanceCounter() - lastUpdate) / (float)SDL_GetPerformanceFrequency()) * 1000;

				renderer->camera.Update(deltaTime);

				//mise à jour de l'affichage
				renderer->Update(Scene::mainScene);
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