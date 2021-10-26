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
float particleLinkLength = 2;

ForcesRegister forcesRegister;

Particle* CreateParticle(Scene* scene, Vector3D pos, Vector3D velocity = Vector3D(0, 0, 0))
{
	Particle* p = new Particle(pos, particleMass);
	scene->AddParticle(p);
	p->SetVelocity(velocity);

	forcesRegister.AddEntry(p, new ParticleGravityGenerator());
	forcesRegister.AddEntry(p, new ParticleDampingGenerator());

	return p;
}

void CreateSpring(Scene* scene)
{
	//création des particles
	Particle* p1 = new Particle(Vector3D(-2, 2, 0), particleMass);
	scene->AddParticle(p1);
	Particle* p2 = new Particle(Vector3D(2, 2, 0), particleMass * 2);
	scene->AddParticle(p2);

	//création des forces
	forcesRegister.AddEntry(p1, new ParticleDampingGenerator());
	forcesRegister.AddEntry(p1, new ParticleSpringGenerator(p2));
	forcesRegister.AddEntry(p2, new ParticleDampingGenerator());
	forcesRegister.AddEntry(p2, new ParticleSpringGenerator(p1));
}

//crée deux particules reliées par une tige
void CreateRod(Scene* scene, ParticleContactSolver* contactSolver)
{
	//création des particules
	CreateParticle(scene, Vector3D(-particleLinkLength * 0.5f, 2, 0), Vector3D(rand() % 10 - 5, rand() % 10 - 5, 0));
	CreateParticle(scene, Vector3D(particleLinkLength * 0.5f, 2, 0), Vector3D(rand() % 10 - 5, rand() % 10 - 5, 0));
	
	//on récupère des pointeurs vers ces particules...
	Particle* first = scene->gameObjects[scene->gameObjects.size() - 2];
	Particle* second = scene->gameObjects[scene->gameObjects.size() - 1];

	//...puis on crée le lien
	ParticleRod* rod = new ParticleRod(first, second, particleLinkLength);
	contactSolver->generator.AddParticleLink(rod);
}

//crée deux particules reliées par un cable
void CreateCable(Scene* scene, ParticleContactSolver* contactSolver)
{
	//création des particules
	CreateParticle(scene, Vector3D(-particleLinkLength * 0.5f, 2, 0), Vector3D(rand() % 10 - 5, rand() % 10 - 5, 0));
	CreateParticle(scene, Vector3D(particleLinkLength * 0.5f, 2, 0), Vector3D(rand() % 10 - 5, rand() % 10 - 5, 0));

	//on récupère des pointeurs vers ces particules...
	Particle* first = scene->gameObjects[scene->gameObjects.size() - 2];
	Particle* second = scene->gameObjects[scene->gameObjects.size() - 1];

	//...puis on crée le lien
	ParticleCable* cable = new ParticleCable(first, second, particleLinkLength);
	contactSolver->generator.AddParticleLink(cable);
}

//créer un cube composé de 8 particules reliées par des tiges
void CreateRodCube(Scene* scene, ParticleContactSolver* contactSolver)
{
	float halfLen = particleLinkLength * 0.5f;

	//création des particules
	std::vector<Particle*> particles;
	particles.push_back(CreateParticle(scene, Vector3D(-halfLen, halfLen + 2, -halfLen), Vector3D(20, 10, rand() % 10 - 5))); //côté avant haut-gauche
	particles.push_back(CreateParticle(scene, Vector3D(halfLen, halfLen + 2, -halfLen), Vector3D(0, 0, 0))); // côté avant haut-droit
	particles.push_back(CreateParticle(scene, Vector3D(-halfLen, -halfLen + 2, -halfLen), Vector3D(0, 0, 0))); //côté avant bas-gauche
	particles.push_back(CreateParticle(scene, Vector3D(halfLen, -halfLen + 2, -halfLen), Vector3D(0, 0, 0))); //côté avant bas-droit
	particles.push_back(CreateParticle(scene, Vector3D(-halfLen, halfLen + 2, halfLen), Vector3D(0, 0, 0))); //côté arrière haut-gauche
	particles.push_back(CreateParticle(scene, Vector3D(halfLen, halfLen + 2, halfLen), Vector3D(0, 0, 0))); // côté arrière haut-droit
	particles.push_back(CreateParticle(scene, Vector3D(-halfLen, -halfLen + 2, halfLen), Vector3D(0, 0, 0))); //côté arrière bas-gauche
	particles.push_back(CreateParticle(scene, Vector3D(halfLen, -halfLen + 2, halfLen), Vector3D(0, 0, 0))); //côté arrière bas-droit

	for (int i = 0; i < 8; i++)
	{
		for (int j = i + 1; j < 8; j++)
		{
			float length = Vector3D::Norm(particles[i]->GetPosition() - particles[j]->GetPosition());
			contactSolver->generator.AddParticleLink(new ParticleRod(particles[i], particles[j], length));
		}
	}
}

//supprime tout les éléments de la scène
void ResetScene(Scene* scene, ParticleContactSolver* contactSolver)
{
	contactSolver->generator.RemoveAllParticleLink();
	for (int i = Scene::mainScene->gameObjects.size() - 1; i >= 0; i--)
	{
		Scene::mainScene->RemoveParticle(Scene::mainScene->gameObjects[i]);
	}
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
				float randZ = (-100 + rand() % 200) * randomZDirection * 0.01f;
				CreateParticle(Scene::mainScene, Vector3D(0, 1, 0), Vector3D(-10 + mouseX * 20, mouseY * 15, randZ));
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

//création de la fenetre graphique
void MakeImGuiWindow(float physicsUpdateTime, ParticleContactSolver* solver)
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

	ImGui::Dummy(ImVec2(0.0f, 20.0f));
	ImGui::PushItemWidth(150);

	ImGui::SliderFloat("Taille du lien", &particleLinkLength, 0, 5, "%.1f");

	if (ImGui::Button("Creer tige", ImVec2(148, 20)))
		CreateRod(Scene::mainScene, solver);
	ImGui::SameLine(160);
	if (ImGui::Button("Creer cable", ImVec2(148, 20)))
		CreateCable(Scene::mainScene, solver);

	if (ImGui::Button("Creer ressort", ImVec2(148, 20)))
		CreateSpring(Scene::mainScene);
	ImGui::SameLine(160);
	if (ImGui::Button("Creer cube de tiges", ImVec2(148, 20)))
		CreateRodCube(Scene::mainScene, solver);

	ImGui::Dummy(ImVec2(0.0f, 20.0f));
	ImGui::PushItemWidth(150);

	if (ImGui::Button("Reset Scene", ImVec2(300, 20)))
		ResetScene(Scene::mainScene, solver);

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

			ParticleContactSolver* particleContactSolver = new ParticleContactSolver();

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
				MakeImGuiWindow(physicsUpdateTime, particleContactSolver);
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