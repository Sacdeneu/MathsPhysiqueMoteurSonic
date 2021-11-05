#include <SDL.h>
#include <stdio.h>
#include <stdlib.h> 
#include "rendering/renderer.h"
#include "rendering/scene.h"
#include "math/Vector3D.h"
#include "Physics/forcesRegister.h"
#include "Physics/particleGravityGenerator.h"
#include "Physics/particleDampingGenerator.h"
#include "Physics/particleAnchoredSpringGenerator.h"
#include "Physics/particleSpringGenerator.h"
#include "Physics/particleBungeeGenerator.h"
#include "Physics/particleArchimedeGenerator.h"

#include "Physics/ParticleContactSolver.h"
#include "Physics/ParticleCable.h"
#include "Physics/ParticleRod.h"

#include "math/Matrix4.h"

bool runGame = true;
float particleMass = 1;
float randomZDirection = 0;// 2.5f;
float particleLinkLength = 2;

ForcesRegister forcesRegister;
ParticleContactSolver particleContactSolver;

//############################
//#                          #
//#  CREATION DE PARTICULES  #
//#                          #
//############################


// Cr�ation d'une particule selon les param�tres g�r�s par la fen�tre ImGUI.
// La particule cr��e est soumise � la gravit� et au damping.
Particle* CreateParticle(Scene* scene, Vector3D pos, Vector3D velocity = Vector3D(0, 0, 0), float massFactor = 1)
{
	Particle* p = new Particle(pos, particleMass * massFactor);
	scene->AddParticle(p);
	p->SetVelocity(velocity);

	forcesRegister.AddEntry(p, new ParticleGravityGenerator());
	forcesRegister.AddEntry(p, new ParticleDampingGenerator());

	return p;
}


// Cr�ation de deux particules li�es par un ressort selon les param�tres g�r�s par la fen�tre ImGUI.
// Les deux particule cr��es sont soumises aux forces g�n�r�es par le ressort et au damping
void CreateSpring(Scene* scene)
{
	//cr�ation des particles
	Particle* p1 = new Particle(Vector3D(-2, 2, 0), particleMass);
	scene->AddParticle(p1);
	Particle* p2 = new Particle(Vector3D(2, 2, 0), particleMass * 2);
	scene->AddParticle(p2);

	//cr�ation des forces
	forcesRegister.AddEntry(p1, new ParticleDampingGenerator());
	forcesRegister.AddEntry(p1, new ParticleSpringGenerator(p2, particleLinkLength));
	forcesRegister.AddEntry(p2, new ParticleDampingGenerator());
	forcesRegister.AddEntry(p2, new ParticleSpringGenerator(p1, particleLinkLength));
}

// Cr�ation d'une particule li�e par un ressort.
// Le ressort est � une position fixe.
void CreateAnchoredSpring(Scene* scene)
{
	//cr�ation des particules
	Particle* p = CreateParticle(scene, Vector3D(0, 2, 0), Vector3D(10, 0, randomZDirection));
	forcesRegister.AddEntry(p, new ParticleAnchoredSpringGenerator(Vector3D(0, 5, 0), particleLinkLength));
}

// Cr�ation de deux particules reli�es par un �lastique de bungee.
// Les deux particule cr��es sont soumises aux forces g�n�r�es par l'�lastique de bungee et au damping
void CreateBungee(Scene* scene)
{
	//cr�ation des particles
	Particle* p1 = new Particle(Vector3D(-5, 2, 0), particleMass);
	scene->AddParticle(p1);
	Particle* p2 = new Particle(Vector3D(5, 2, 0), particleMass * 2);
	scene->AddParticle(p2);

	//cr�ation des forces
	forcesRegister.AddEntry(p1, new ParticleDampingGenerator());
	forcesRegister.AddEntry(p1, new ParticleBungeeGenerator(p2, particleLinkLength));
	forcesRegister.AddEntry(p2, new ParticleDampingGenerator());
	forcesRegister.AddEntry(p2, new ParticleBungeeGenerator(p1, particleLinkLength));
}

//cr�e deux particules reli�es par une tige
void CreateRod(Scene* scene)
{
	//cr�ation des particules
	CreateParticle(scene, Vector3D(-particleLinkLength * 0.5f, 2, 0), Vector3D(rand() % 10 - 5, rand() % 10 - 5, 0));
	CreateParticle(scene, Vector3D(particleLinkLength * 0.5f, 2, 0), Vector3D(rand() % 10 - 5, rand() % 10 - 5, 0));
	
	//on r�cup�re des pointeurs vers ces particules...
	Particle* first = scene->gameObjects[scene->gameObjects.size() - 2];
	Particle* second = scene->gameObjects[scene->gameObjects.size() - 1];

	//...puis on cr�e le lien
	ParticleRod* rod = new ParticleRod(first, second, particleLinkLength);
	particleContactSolver.generator.AddParticleLinks(rod);
}

//cr�e deux particules reli�es par un cable
void CreateCable(Scene* scene)
{
	//cr�ation des particules
	CreateParticle(scene, Vector3D(-particleLinkLength * 0.5f, 2, 0), Vector3D(rand() % 10 - 5, rand() % 10 - 5, 0));
	CreateParticle(scene, Vector3D(particleLinkLength * 0.5f, 2, 0), Vector3D(rand() % 10 - 5, rand() % 10 - 5, 0));

	//on r�cup�re des pointeurs vers ces particules...
	Particle* first = scene->gameObjects[scene->gameObjects.size() - 2];
	Particle* second = scene->gameObjects[scene->gameObjects.size() - 1];

	//...puis on cr�e le lien
	ParticleCable* cable = new ParticleCable(first, second, particleLinkLength);
	particleContactSolver.generator.AddParticleLinks(cable);
}

//cr�ation d'un cube compos� de 8 particules reli�es par des tiges
void CreateRodCube(Scene* scene)
{
	float halfLen = particleLinkLength * 0.5f;

	//cr�ation des particules
	std::vector<Particle*> particles;
	particles.push_back(CreateParticle(scene, Vector3D(-halfLen, halfLen + 2, -halfLen), Vector3D(20, 10, rand() % 10 - 5))); //c�t� avant haut-gauche
	particles.push_back(CreateParticle(scene, Vector3D(halfLen, halfLen + 2, -halfLen), Vector3D(0, 0, 0))); // c�t� avant haut-droit
	particles.push_back(CreateParticle(scene, Vector3D(-halfLen, -halfLen + 2, -halfLen), Vector3D(0, 0, 0))); //c�t� avant bas-gauche
	particles.push_back(CreateParticle(scene, Vector3D(halfLen, -halfLen + 2, -halfLen), Vector3D(0, 0, 0))); //c�t� avant bas-droit
	particles.push_back(CreateParticle(scene, Vector3D(-halfLen, halfLen + 2, halfLen), Vector3D(0, 0, 0))); //c�t� arri�re haut-gauche
	particles.push_back(CreateParticle(scene, Vector3D(halfLen, halfLen + 2, halfLen), Vector3D(0, 0, 0))); // c�t� arri�re haut-droit
	particles.push_back(CreateParticle(scene, Vector3D(-halfLen, -halfLen + 2, halfLen), Vector3D(0, 0, 0))); //c�t� arri�re bas-gauche
	particles.push_back(CreateParticle(scene, Vector3D(halfLen, -halfLen + 2, halfLen), Vector3D(0, 0, 0))); //c�t� arri�re bas-droit

	// cr�ation des liens
	for (int i = 0; i < 8; i++)
	{
		for (int j = i + 1; j < 8; j++)
		{
			float length = Vector3D::Norm(particles[i]->GetPosition() - particles[j]->GetPosition());
			particleContactSolver.generator.AddParticleLinks(new ParticleRod(particles[i], particles[j], length));
		}
	}
}

// Cr�ation d'une particule soumise aux forces de flottaison (Archim�de)
void CreateArchimede(Scene* scene)
{
	//cr�ation des particules
	Particle* p = CreateParticle(scene, Vector3D(20, 10, 0), Vector3D(0, 0, 0));
	forcesRegister.AddEntry(p, new ParticleArchimedeGenerator());
}

//##########
//#        #
//#  BLOB  #
//#        #
//##########

float blobMoveX, blobMoveY = 0;
float blobForce = 4;
std::vector<Particle*> blobElements;

// Update les inputs du joueur pour d�placer le blob.
void UpdateBlobInput(SDL_Keycode key, bool state)
{
	if (key == SDLK_UP) blobMoveY = state ? 1 : 0;
	else if (key == SDLK_LEFT) blobMoveX = state ? -1 : 0;
	else if (key == SDLK_DOWN) blobMoveY = state ? -1 : 0;
	else if (key == SDLK_RIGHT) blobMoveX = state ? 1 : 0;
}

// Attache une nouvelle particule au Blob
void AttachNewBlobElement(Particle* p)
{
	// Set le flag pour bien dire que la particule est une particule de blob
	p->isBlob = true;

	// On parcourt les �l�ments du blob pour cr�er les liaisons
	for (int j = 0; j < blobElements.size(); j++)
	{
		Particle* other = blobElements[j];
		// On applique une liaison de mani�re al�atoire pour ne pas surcharger le blob de lien dans tous les sens
		if (other != p && rand() % 10 < 4) 
		{
			// On cr�e le c�ble et le ressort entre les deux particules.
			Particle* other = blobElements[j];
			float length = Vector3D::Norm(p->GetPosition() - blobElements[j]->GetPosition());
			forcesRegister.AddEntry(p, new ParticleSpringGenerator(other, length * 0.5f));
			forcesRegister.AddEntry(other, new ParticleSpringGenerator(p, length * 0.5f));
			particleContactSolver.generator.AddParticleLinks(new ParticleCable(p, other, length * 2));
		}
	}
}

void SliceBlob()
{
	//TODO: fix cet enfer
	/*
	for (int i = 0; i < blobElements.size(); i++)
	{
		Particle* p = blobElements[i];
		blobElements.erase(std::remove(blobElements.begin(), blobElements.end(), p), blobElements.end());
		forcesRegister.DeleteParticle(p);
		particleContactSolver.generator.RemoveAllLinksFromParticle(p->id);
		forcesRegister.AddEntry(p, new ParticleGravityGenerator());
		forcesRegister.AddEntry(p, new ParticleDampingGenerator());
		p->isBlob = false;
	}
	*/
}

// Update la position du blob et on check s'il peut absorber des nouvelles particules.
void UpdateBlobForce()
{
	// Applique le d�placement du blob (sur toutes les particules constituant le blob pour cr�er moins de probl�mes)
	for (int i = 0; i < blobElements.size(); i++)
		blobElements[i]->AddForce(Vector3D(blobMoveX * blobForce, 0, -blobMoveY * blobForce));


	// On parcourt la liste des contacts du particleContactSolver pour d�terminer 
	// qui est entr� en contact avec le blob.
	for (int i = 0; i < particleContactSolver.contactsLastFrame.size(); i++)
	{
		ParticleContact* contact = &particleContactSolver.contactsLastFrame.at(i);
		// Si le contact est entre une particule blob et une particule non blob...
		if (contact->GetParticleA()->isBlob != contact->GetParticleB()->isBlob && !contact->GetParticleB()->isAABB)
		{
			// ...on attache la particule au blob.
			AttachNewBlobElement(contact->GetParticleA()->isBlob ? contact->GetParticleB() : contact->GetParticleA());
		}
	}
}



// Cr�ation d'un blob
void CreateBlob()
{
	for (int i = 0; i < 20; i++)
	{
		// cr�e une particule et l'ajoute � une liste repr�sentant tous les �l�ments du blob
		// les particules spawn en grille.
		Particle* p = CreateParticle(Scene::mainScene, Vector3D(i % 5, 3, i / 5), Vector3D(0, 1, 0), (rand() % 150 + 50) / 200.0f);
		blobElements.push_back(p);
		
		// Attache la particule aux �l�ments de la liste du blob.
		AttachNewBlobElement(p);
	}
}

// Cr�ation d'un serpent
void CreateSnake(Scene* scene)
{
	//cr�ation des particules
	std::vector<Particle*> particles;
	int nbParticle = 10;
	float size = cbrt(particleMass) * 0.8f;
	float spawnX = -6;

	// Fait appara�tre les particules en ligne droite et les attaches via une tige
	for (int i = 0; i < nbParticle; i++)
	{
		spawnX += size;
		particles.push_back(CreateParticle(scene, Vector3D(spawnX, 1, 0), Vector3D(2, 0, (rand() % 10 - 5) / 5.0f)));
		if(i > 0)
			particleContactSolver.generator.AddParticleLinks(new ParticleRod(particles[i], particles[i - 1], size));
	}
	particles[nbParticle-1]->SetVelocity(Vector3D(20, 0, 0));
}

//##########
//#        #
//#  MAIN  #
//#        #
//##########

//supprime tous les �l�ments de la sc�ne
void ResetScene(Scene* scene)
{
	particleContactSolver.generator.RemoveAllParticleLink();
	blobElements.clear();
	for (int i = Scene::mainScene->gameObjects.size() - 1; i >= 0; i--)
	{
		Scene::mainScene->RemoveParticle(Scene::mainScene->gameObjects[i]);
	}
}

bool mouseButtonDown = false;
// G�re les inputs pour d�placer la cam�ra et faire spawn des objets.
int HandleInputs(Renderer* renderer)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT: //ferme le jeu quand on ferme la fen�tre
			runGame = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_SPACE) // Fait spawn une particule en fonction de la position de la souris
			{
				int pixelMouseX, pixelMouseY;
				SDL_GetMouseState(&pixelMouseX, &pixelMouseY);
				float mouseX = pixelMouseX * 1.0f / SCREEN_WIDTH;
				float mouseY = 1 - (pixelMouseY * 1.0f / SCREEN_HEIGHT);
				float randZ = (-100 + rand() % 200) * randomZDirection * 0.01f;
				CreateParticle(Scene::mainScene, Vector3D(0, 1, 0), Vector3D(-10 + mouseX * 20, mouseY * 15, randZ));
			}
			else if (event.key.keysym.sym == 'r') // D�coupe le blob
				SliceBlob();
			else
			{
				// Update les d�placements cam�ra et blob
				renderer->camera.UpdateKeyboardInput(event.key.keysym.sym, true);
				UpdateBlobInput(event.key.keysym.sym, true);
			}
			break;

		case SDL_KEYUP: // Update les d�placements cam�ra et blob pour qu'ils s'arr�tent
			renderer->camera.UpdateKeyboardInput(event.key.keysym.sym, false);
			UpdateBlobInput(event.key.keysym.sym, false);
			break;

		case SDL_MOUSEMOTION: // Rotate la cam�ra si le clic souris est maintenu.
			if(mouseButtonDown)
				renderer->camera.UpdateMouseInput(event.motion.xrel, event.motion.yrel);
			break;

		case SDL_MOUSEBUTTONDOWN: // clic souris maintenu
			if (event.button.button == SDL_BUTTON_RIGHT)
				mouseButtonDown = true;
			break;

		case SDL_MOUSEBUTTONUP: // clic souris relach�
			if (event.button.button == SDL_BUTTON_RIGHT)
				mouseButtonDown = false;
			break;

		default:
			break;
		}
	}
	return 1;
}

//cr�ation de la fenetre graphique
// contient principalement des fonctions debug / tests
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

	ImGui::Dummy(ImVec2(0.0f, 20.0f));
	ImGui::PushItemWidth(150);

	ImGui::SliderFloat("Taille du lien", &particleLinkLength, 0, 5, "%.1f");

	
	if (ImGui::Button("Creer ressort ancre", ImVec2(148, 20)))
		CreateAnchoredSpring(Scene::mainScene);
	ImGui::SameLine(160);
	if (ImGui::Button("Creer ressort", ImVec2(148, 20)))
		CreateSpring(Scene::mainScene);
	
	if (ImGui::Button("Creer bungee", ImVec2(148, 20)))
		CreateBungee(Scene::mainScene);
	ImGui::SameLine(160);
	if (ImGui::Button("Creer balle flottante", ImVec2(148, 20)))
		CreateArchimede(Scene::mainScene);

	if (ImGui::Button("Creer tige", ImVec2(148, 20)))
		CreateRod(Scene::mainScene);
	ImGui::SameLine(160);
	if (ImGui::Button("Creer cable", ImVec2(148, 20)))
		CreateCable(Scene::mainScene);

	if (ImGui::Button("Creer serpent", ImVec2(148, 20)))
		CreateSnake(Scene::mainScene);
	ImGui::SameLine(160);
	if (ImGui::Button("Creer cube de tiges", ImVec2(148, 20)))
		CreateRodCube(Scene::mainScene);

	if (ImGui::Button("Creer blob", ImVec2(300, 20)))
		CreateBlob();

	

	ImGui::Dummy(ImVec2(0.0f, 20.0f));
	ImGui::PushItemWidth(150);

	if (ImGui::Button("Reset Scene", ImVec2(300, 20)))
		ResetScene(Scene::mainScene);

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main( int argc, char* args[])
{
	Matrix4 testMat1;
	Matrix4 testMat2;
	std::cout << "Matrice test :\n" << testMat1 << std::endl;
	testMat2.SetValue(3.1415f, 2, 2);
	testMat2 = testMat1 + testMat2;
	std::cout << "Matrice test :\n" << testMat2 << std::endl;
	testMat2 = testMat1 * testMat2;
	std::cout << "Matrice test :\n" << testMat2 << std::endl;
	testMat2 = testMat2 * testMat2;
	std::cout << "Matrice test :\n" << testMat2 << std::endl;

	//initialisation
	SDL_Window* window = NULL;
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Erreur de l'initalisation de SDL : %s\n", SDL_GetError());
	}
	else
	{
		//cr�ation de la fen�tre
		window = SDL_CreateWindow("Sonic Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
		if(window == NULL)
		{
			printf("Erreur de cr�ation de la fen�tre ! SDL_Error: %s\n", SDL_GetError() );
		}
		else //si la fen�tre a �t� cr�e
		{
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui::StyleColorsDark();

			// initialisation du renderer et de la sc�ne
			Renderer* renderer = new Renderer(window);
			Scene::mainScene = new Scene(&forcesRegister);

			Uint64 lastUpdate = SDL_GetPerformanceCounter();

			//boucle de jeu
			while (runGame)
			{
				//mise � jour des entr�es
				HandleInputs(renderer);

				//calcul de dt
				Uint64 now = SDL_GetPerformanceCounter();
				float deltaTime = ((now - lastUpdate) / (float)SDL_GetPerformanceFrequency());
				lastUpdate = now;

				//mise � jour de la physique et de la logique
				forcesRegister.Update(deltaTime);
				Scene::mainScene->Update(deltaTime);
				UpdateBlobForce();
				
				//test collisions
				particleContactSolver.UpdateCollisions(Scene::mainScene, 4);
				float physicsUpdateTime = ((SDL_GetPerformanceCounter() - lastUpdate) / (float)SDL_GetPerformanceFrequency()) * 1000;

				renderer->camera.Update(deltaTime);

				//mise � jour de l'affichage
				renderer->Update(Scene::mainScene);
				MakeImGuiWindow(physicsUpdateTime);
				SDL_GL_SwapWindow(window);

				//rendu � 60FPS
				SDL_Delay(1000 / 60);
			}
			
			delete renderer;
			delete Scene::mainScene;
		}
	}

	//destruction de la fen�tre
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}