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
#include "math/Matrix3.h"

#include "math/Quaternion.h"

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


// Création d'une particule selon les paramètres gérés par la fenêtre ImGUI.
// La particule créée est soumise à la gravité et au damping.
Particle* CreateParticle(Scene* scene, Vector3D pos, Vector3D velocity = Vector3D(0, 0, 0), float massFactor = 1)
{
	Particle* p = new Particle(pos, particleMass * massFactor);
	scene->AddParticle(p);
	p->SetVelocity(velocity);

	forcesRegister.AddEntry(p, new ParticleGravityGenerator());
	forcesRegister.AddEntry(p, new ParticleDampingGenerator());

	return p;
}


// Création de deux particules liées par un ressort selon les paramètres gérés par la fenêtre ImGUI.
// Les deux particule créées sont soumises aux forces générées par le ressort et au damping
void CreateSpring(Scene* scene)
{
	//création des particles
	Particle* p1 = new Particle(Vector3D(-2, 2, 0), particleMass);
	scene->AddParticle(p1);
	Particle* p2 = new Particle(Vector3D(2, 2, 0), particleMass * 2);
	scene->AddParticle(p2);

	//création des forces
	forcesRegister.AddEntry(p1, new ParticleDampingGenerator());
	forcesRegister.AddEntry(p1, new ParticleSpringGenerator(p2, particleLinkLength));
	forcesRegister.AddEntry(p2, new ParticleDampingGenerator());
	forcesRegister.AddEntry(p2, new ParticleSpringGenerator(p1, particleLinkLength));
}

// Création d'une particule liée par un ressort.
// Le ressort est à une position fixe.
void CreateAnchoredSpring(Scene* scene)
{
	//création des particules
	Particle* p = CreateParticle(scene, Vector3D(0, 2, 0), Vector3D(10, 0, randomZDirection));
	forcesRegister.AddEntry(p, new ParticleAnchoredSpringGenerator(Vector3D(0, 5, 0), particleLinkLength));
}

// Création de deux particules reliées par un élastique de bungee.
// Les deux particule créées sont soumises aux forces générées par l'élastique de bungee et au damping
void CreateBungee(Scene* scene)
{
	//création des particles
	Particle* p1 = new Particle(Vector3D(-5, 2, 0), particleMass);
	scene->AddParticle(p1);
	Particle* p2 = new Particle(Vector3D(5, 2, 0), particleMass * 2);
	scene->AddParticle(p2);

	//création des forces
	forcesRegister.AddEntry(p1, new ParticleDampingGenerator());
	forcesRegister.AddEntry(p1, new ParticleBungeeGenerator(p2, particleLinkLength));
	forcesRegister.AddEntry(p2, new ParticleDampingGenerator());
	forcesRegister.AddEntry(p2, new ParticleBungeeGenerator(p1, particleLinkLength));
}

//crée deux particules reliées par une tige
void CreateRod(Scene* scene)
{
	//création des particules
	CreateParticle(scene, Vector3D(-particleLinkLength * 0.5f, 2, 0), Vector3D(rand() % 10 - 5, rand() % 10 - 5, 0));
	CreateParticle(scene, Vector3D(particleLinkLength * 0.5f, 2, 0), Vector3D(rand() % 10 - 5, rand() % 10 - 5, 0));
	
	//on récupère des pointeurs vers ces particules...
	Particle* first = scene->gameObjects[scene->gameObjects.size() - 2];
	Particle* second = scene->gameObjects[scene->gameObjects.size() - 1];

	//...puis on crée le lien
	ParticleRod* rod = new ParticleRod(first, second, particleLinkLength);
	particleContactSolver.generator.AddParticleLinks(rod);
}

//crée deux particules reliées par un cable
void CreateCable(Scene* scene)
{
	//création des particules
	CreateParticle(scene, Vector3D(-particleLinkLength * 0.5f, 2, 0), Vector3D(rand() % 10 - 5, rand() % 10 - 5, 0));
	CreateParticle(scene, Vector3D(particleLinkLength * 0.5f, 2, 0), Vector3D(rand() % 10 - 5, rand() % 10 - 5, 0));

	//on récupère des pointeurs vers ces particules...
	Particle* first = scene->gameObjects[scene->gameObjects.size() - 2];
	Particle* second = scene->gameObjects[scene->gameObjects.size() - 1];

	//...puis on crée le lien
	ParticleCable* cable = new ParticleCable(first, second, particleLinkLength);
	particleContactSolver.generator.AddParticleLinks(cable);
}

//création d'un cube composé de 8 particules reliées par des tiges
void CreateRodCube(Scene* scene)
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

	// création des liens
	for (int i = 0; i < 8; i++)
	{
		for (int j = i + 1; j < 8; j++)
		{
			float length = Vector3D::Norm(particles[i]->GetPosition() - particles[j]->GetPosition());
			particleContactSolver.generator.AddParticleLinks(new ParticleRod(particles[i], particles[j], length));
		}
	}
}

// Création d'une particule soumise aux forces de flottaison (Archimède)
void CreateArchimede(Scene* scene)
{
	//création des particules
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

// Update les inputs du joueur pour déplacer le blob.
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

	// On parcourt les éléments du blob pour créer les liaisons
	for (int j = 0; j < blobElements.size(); j++)
	{
		Particle* other = blobElements[j];
		// On applique une liaison de manière aléatoire pour ne pas surcharger le blob de lien dans tous les sens
		if (other != p && rand() % 10 < 4) 
		{
			// On crée le câble et le ressort entre les deux particules.
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
	// Applique le déplacement du blob (sur toutes les particules constituant le blob pour créer moins de problèmes)
	for (int i = 0; i < blobElements.size(); i++)
		blobElements[i]->AddForce(Vector3D(blobMoveX * blobForce, 0, -blobMoveY * blobForce));


	// On parcourt la liste des contacts du particleContactSolver pour déterminer 
	// qui est entré en contact avec le blob.
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



// Création d'un blob
void CreateBlob()
{
	for (int i = 0; i < 20; i++)
	{
		// crée une particule et l'ajoute à une liste représentant tous les éléments du blob
		// les particules spawn en grille.
		Particle* p = CreateParticle(Scene::mainScene, Vector3D(i % 5, 3, i / 5), Vector3D(0, 1, 0), (rand() % 150 + 50) / 200.0f);
		blobElements.push_back(p);
		
		// Attache la particule aux éléments de la liste du blob.
		AttachNewBlobElement(p);
	}
}

// Création d'un serpent
void CreateSnake(Scene* scene)
{
	//création des particules
	std::vector<Particle*> particles;
	int nbParticle = 10;
	float size = cbrt(particleMass) * 0.8f;
	float spawnX = -6;

	// Fait apparaître les particules en ligne droite et les attaches via une tige
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

//supprime tous les éléments de la scène
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
			if (event.key.keysym.sym == SDLK_SPACE) // Fait spawn une particule en fonction de la position de la souris
			{
				int pixelMouseX, pixelMouseY;
				SDL_GetMouseState(&pixelMouseX, &pixelMouseY);
				float mouseX = pixelMouseX * 1.0f / SCREEN_WIDTH;
				float mouseY = 1 - (pixelMouseY * 1.0f / SCREEN_HEIGHT);
				float randZ = (-100 + rand() % 200) * randomZDirection * 0.01f;
				CreateParticle(Scene::mainScene, Vector3D(0, 1, 0), Vector3D(-10 + mouseX * 20, mouseY * 15, randZ));
			}
			else if (event.key.keysym.sym == 'r') // Découpe le blob
				SliceBlob();
			else
			{
				// Update les déplacements caméra et blob
				renderer->camera.UpdateKeyboardInput(event.key.keysym.sym, true);
				UpdateBlobInput(event.key.keysym.sym, true);
			}
			break;

		case SDL_KEYUP: // Update les déplacements caméra et blob pour qu'ils s'arrêtent
			renderer->camera.UpdateKeyboardInput(event.key.keysym.sym, false);
			UpdateBlobInput(event.key.keysym.sym, false);
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

	Matrix3 testMat3;
	Matrix3 testMat4;
	testMat3.SetValue(3.1415f, 1, 2); testMat3.SetValue(10, 2, 0);
	testMat4 = testMat3.pow(5);
	std::cout << "Matrice test :\n" << testMat4 << std::endl;

	Matrix3 testMat5;
	testMat5 = testMat4.Transpose();
	std::cout << "Matrice transpose :\n" << testMat5 << std::endl;

	Matrix3 testMat6;
	testMat6.SetValue(2, 0, 0);
	testMat6.SetValue(2, 0, 1);
	testMat6.SetValue(3, 0, 2);
	testMat6.SetValue(4, 1, 0);
	testMat6.SetValue(5, 1, 1);
	testMat6.SetValue(6, 1, 2);
	testMat6.SetValue(7, 2, 0);
	testMat6.SetValue(8, 2, 1);
	testMat6.SetValue(9, 2, 2);
	std::cout << "Matrice test6 :\n" << testMat6 << std::endl;

	float det1;
	det1 = testMat6.Determinant();
	std::cout << "Determinant :\n" << det1 << std::endl;

	Matrix3 testMat7;
	testMat7 = testMat6.Inverse(det1);
	std::cout << "Inverse :\n" << testMat7 << std::endl;


	// Test Quaternion
	#pragma region TestQuaternion

	Quaternion q(1, 0, 0, 0);
	Quaternion q2(0, 0, 0, 1);
	q.Normalize();
	q2.Normalize();
	std::cout << q << std::endl;
	std::cout << q2 << std::endl;

	Quaternion q3 = q * q2;
	std::cout << q3 << std::endl;

	Vector3D v(5, 2, 3);
	Quaternion q4(0, 1, 0, 1);
	q4.Normalize();
	std::cout << (q4 * v) << std::endl;

	Quaternion q5(1, 0, 1, 0);
	q5.Normalize();
	std::cout << (q5 * v) << std::endl;
	#pragma endregion




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
				forcesRegister.Update(deltaTime);
				Scene::mainScene->Update(deltaTime);
				UpdateBlobForce();
				
				//test collisions
				particleContactSolver.UpdateCollisions(Scene::mainScene, 4);
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