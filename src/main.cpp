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

bool runGame = true;
float rigidbodyMass = 1;
float randomZDirection = 0;// 2.5f;
float rigidbodyLinkLength = 2;

ForcesRegister forcesRegister;
RigidbodyContactSolver contactSolver;

//############################
//#                          #
//#  CREATION DE RIGIBDODY   #
//#                          #
//############################


// Cr�ation d'un rigidbody selon les param�tres g�r�s par la fen�tre ImGUI.
// Le rigidbody cr�� est soumis � la gravit� et au damping.
Rigidbody* Createrigidbody(Scene* scene, Vector3D pos, Vector3D velocity = Vector3D(0, 0, 0), float massFactor = 1)
{
	Rigidbody* p = new Rigidbody(pos, rigidbodyMass * massFactor);
	scene->Addrigidbody(p);
	p->SetVelocity(velocity);
	p->AddForceAtPoint(Vector3D(0, 1, 0), Vector3D(velocity.x * 50, 0, 0));

	forcesRegister.AddEntry(p, new RigidbodyGravityGenerator());
	forcesRegister.AddEntry(p, new RigidbodyDampingGenerator());

	return p;
}


// Cr�ation de deux rigibodys li�s par un ressort selon les param�tres g�r�s par la fen�tre ImGUI.
// Les deux rigidbody cr��s sont soumises aux forces g�n�r�es par le ressort et au damping
void CreateSpring(Scene* scene)
{
	//cr�ation des rigidbodys
	Rigidbody* p1 = new Rigidbody(Vector3D(-2, 2, 0), rigidbodyMass);
	scene->Addrigidbody(p1);
	Rigidbody* p2 = new Rigidbody(Vector3D(2, 2, 0), rigidbodyMass * 2);
	scene->Addrigidbody(p2);

	//cr�ation des forces
	forcesRegister.AddEntry(p1, new RigidbodyDampingGenerator());
	forcesRegister.AddEntry(p1, new RigidbodySpringGenerator(p2, rigidbodyLinkLength));
	forcesRegister.AddEntry(p2, new RigidbodyDampingGenerator());
	forcesRegister.AddEntry(p2, new RigidbodySpringGenerator(p1, rigidbodyLinkLength));
}

// Cr�ation d'un rigidbody li�e par un ressort.
// Le ressort est � une position fixe.
void CreateAnchoredSpring(Scene* scene)
{
	//cr�ation des rigidbodys
	Rigidbody* p = Createrigidbody(scene, Vector3D(0, 2, 0), Vector3D(10, 0, randomZDirection));
	forcesRegister.AddEntry(p, new RigidbodyAnchoredSpringGenerator(Vector3D(0, 5, 0), rigidbodyLinkLength));
}

// Cr�ation de deux rigibodys reli�es par un �lastique de bungee.
// Les deux rigibodys cr��s sont soumis aux forces g�n�r�es par l'�lastique de bungee et au damping
void CreateBungee(Scene* scene)
{
	//cr�ation des rigidbodys
	Rigidbody* p1 = new Rigidbody(Vector3D(-5, 2, 0), rigidbodyMass);
	scene->Addrigidbody(p1);
	Rigidbody* p2 = new Rigidbody(Vector3D(5, 2, 0), rigidbodyMass * 2);
	scene->Addrigidbody(p2);

	//cr�ation des forces
	forcesRegister.AddEntry(p1, new RigidbodyDampingGenerator());
	forcesRegister.AddEntry(p1, new RigidbodyBungeeGenerator(p2, rigidbodyLinkLength));
	forcesRegister.AddEntry(p2, new RigidbodyDampingGenerator());
	forcesRegister.AddEntry(p2, new RigidbodyBungeeGenerator(p1, rigidbodyLinkLength));
}

//cr�e deux rigibodys reli�s par une tige
void CreateRod(Scene* scene)
{
	//cr�ation des rigidbodys
	Createrigidbody(scene, Vector3D(-rigidbodyLinkLength * 0.5f, 2, 0), Vector3D(rand() % 10 - 5, rand() % 10 - 5, 0));
	Createrigidbody(scene, Vector3D(rigidbodyLinkLength * 0.5f, 2, 0), Vector3D(rand() % 10 - 5, rand() % 10 - 5, 0));
	
	//on r�cup�re des pointeurs vers ces rigibodys...
	Rigidbody* first = scene->gameObjects[scene->gameObjects.size() - 2];
	Rigidbody* second = scene->gameObjects[scene->gameObjects.size() - 1];

	//...puis on cr�e le lien
	RigidbodyRod* rod = new RigidbodyRod(first, second, rigidbodyLinkLength);
	contactSolver.generator.AddrigidbodyLinks(rod);
}

//cr�e deux rigidbodyss reli�es par un cable
void CreateCable(Scene* scene)
{
	//cr�ation des rigidbodys
	Createrigidbody(scene, Vector3D(-rigidbodyLinkLength * 0.5f, 2, 0), Vector3D(rand() % 10 - 5, rand() % 10 - 5, 0));
	Createrigidbody(scene, Vector3D(rigidbodyLinkLength * 0.5f, 2, 0), Vector3D(rand() % 10 - 5, rand() % 10 - 5, 0));

	//on r�cup�re des pointeurs vers ces rigidbodys...
	Rigidbody* first = scene->gameObjects[scene->gameObjects.size() - 2];
	Rigidbody* second = scene->gameObjects[scene->gameObjects.size() - 1];

	//...puis on cr�e le lien
	RigidbodyCable* cable = new RigidbodyCable(first, second, rigidbodyLinkLength);
	contactSolver.generator.AddrigidbodyLinks(cable);
}

//cr�ation d'un cube compos� de 8 rigidbodys reli�s par des tiges
void CreateRodCube(Scene* scene)
{
	float halfLen = rigidbodyLinkLength * 0.5f;

	//cr�ation des rigidbodys
	std::vector<Rigidbody*> rigidbodys;
	rigidbodys.push_back(Createrigidbody(scene, Vector3D(-halfLen, halfLen + 2, -halfLen), Vector3D(20, 10, rand() % 10 - 5))); //c�t� avant haut-gauche
	rigidbodys.push_back(Createrigidbody(scene, Vector3D(halfLen, halfLen + 2, -halfLen), Vector3D(0, 0, 0))); // c�t� avant haut-droit
	rigidbodys.push_back(Createrigidbody(scene, Vector3D(-halfLen, -halfLen + 2, -halfLen), Vector3D(0, 0, 0))); //c�t� avant bas-gauche
	rigidbodys.push_back(Createrigidbody(scene, Vector3D(halfLen, -halfLen + 2, -halfLen), Vector3D(0, 0, 0))); //c�t� avant bas-droit
	rigidbodys.push_back(Createrigidbody(scene, Vector3D(-halfLen, halfLen + 2, halfLen), Vector3D(0, 0, 0))); //c�t� arri�re haut-gauche
	rigidbodys.push_back(Createrigidbody(scene, Vector3D(halfLen, halfLen + 2, halfLen), Vector3D(0, 0, 0))); // c�t� arri�re haut-droit
	rigidbodys.push_back(Createrigidbody(scene, Vector3D(-halfLen, -halfLen + 2, halfLen), Vector3D(0, 0, 0))); //c�t� arri�re bas-gauche
	rigidbodys.push_back(Createrigidbody(scene, Vector3D(halfLen, -halfLen + 2, halfLen), Vector3D(0, 0, 0))); //c�t� arri�re bas-droit

	// cr�ation des liens
	for (int i = 0; i < 8; i++)
	{
		for (int j = i + 1; j < 8; j++)
		{
			float length = Vector3D::Norm(rigidbodys[i]->GetPosition() - rigidbodys[j]->GetPosition());
			contactSolver.generator.AddrigidbodyLinks(new RigidbodyRod(rigidbodys[i], rigidbodys[j], length));
		}
	}
}

// Cr�ation d'un rigidbody soumis aux forces de flottaison (Archim�de)
void CreateArchimede(Scene* scene)
{
	//cr�ation des rigidbodys
	Rigidbody* p = Createrigidbody(scene, Vector3D(20, 10, 0), Vector3D(0, 0, 0));
	forcesRegister.AddEntry(p, new RigidbodyArchimedeGenerator());
}

//##########
//#        #
//#  BLOB  #
//#        #
//##########

float blobMoveX, blobMoveY = 0;
float blobForce = 4;
std::vector<Rigidbody*> blobElements;

// Update les inputs du joueur pour d�placer le blob.
void UpdateBlobInput(SDL_Keycode key, bool state)
{
	if (key == SDLK_UP) blobMoveY = state ? 1 : 0;
	else if (key == SDLK_LEFT) blobMoveX = state ? -1 : 0;
	else if (key == SDLK_DOWN) blobMoveY = state ? -1 : 0;
	else if (key == SDLK_RIGHT) blobMoveX = state ? 1 : 0;
}

// Attache un nouveau rigidbody au Blob
void AttachNewBlobElement(Rigidbody* p)
{
	// Set le flag pour bien dire que le rigidbody est un rigidbody de blob
	p->isBlob = true;

	// On parcourt les �l�ments du blob pour cr�er les liaisons
	for (int j = 0; j < blobElements.size(); j++)
	{
		Rigidbody* other = blobElements[j];
		// On applique une liaison de mani�re al�atoire pour ne pas surcharger le blob de lien dans tous les sens
		if (other != p && rand() % 10 < 4) 
		{
			// On cr�e le c�ble et le ressort entre les deux rigidbodys.
			Rigidbody* other = blobElements[j];
			float length = Vector3D::Norm(p->GetPosition() - blobElements[j]->GetPosition());
			forcesRegister.AddEntry(p, new RigidbodySpringGenerator(other, length * 0.5f));
			forcesRegister.AddEntry(other, new RigidbodySpringGenerator(p, length * 0.5f));
			contactSolver.generator.AddrigidbodyLinks(new RigidbodyCable(p, other, length * 2));
		}
	}
}

void SliceBlob()
{
	//TODO: fix cet enfer
	/*
	for (int i = 0; i < blobElements.size(); i++)
	{
		rigidbody* p = blobElements[i];
		blobElements.erase(std::remove(blobElements.begin(), blobElements.end(), p), blobElements.end());
		forcesRegister.Deleterigidbody(p);
		contactSolver.generator.RemoveAllLinksFromrigidbody(p->id);
		forcesRegister.AddEntry(p, new rigidbodyGravityGenerator());
		forcesRegister.AddEntry(p, new rigidbodyDampingGenerator());
		p->isBlob = false;
	}
	*/
}

// Update la position du blob et on check s'il peut absorber des nouveaux rigidbodys.
void UpdateBlobForce()
{
	// Applique le d�placement du blob (sur tous les rigidbodys constituant le blob pour cr�er moins de probl�mes)
	for (int i = 0; i < blobElements.size(); i++)
		blobElements[i]->AddForce(Vector3D(blobMoveX * blobForce, 0, -blobMoveY * blobForce));


	// On parcourt la liste des contacts du rigibodyContactSolver pour d�terminer 
	// qui est entr� en contact avec le blob.
	for (int i = 0; i < contactSolver.contactsLastFrame.size(); i++)
	{
		RigidbodyContact* contact = &contactSolver.contactsLastFrame.at(i);
		// Si le contact est entre un rigidbody blob et un rigidbody non blob...
		if (contact->GetrigidbodyA()->isBlob != contact->GetrigidbodyB()->isBlob && !contact->GetrigidbodyB()->isAABB)
		{
			// ...on attache le rigidbody au blob.
			AttachNewBlobElement(contact->GetrigidbodyA()->isBlob ? contact->GetrigidbodyB() : contact->GetrigidbodyA());
		}
	}
}



// Cr�ation d'un blob
void CreateBlob()
{
	for (int i = 0; i < 20; i++)
	{
		// cr�e un rigidbody et l'ajoute � une liste repr�sentant tous les �l�ments du blob
		// les rigidbodys spawn en grille.
		Rigidbody* p = Createrigidbody(Scene::mainScene, Vector3D(i % 5, 3, i / 5), Vector3D(0, 1, 0), (rand() % 150 + 50) / 200.0f);
		blobElements.push_back(p);
		
		// Attache le rigidbody aux �l�ments de la liste du blob.
		AttachNewBlobElement(p);
	}
}

// Cr�ation d'un serpent
void CreateSnake(Scene* scene)
{
	//cr�ation des rigidbodys
	std::vector<Rigidbody*> rigidbodys;
	int nbrigidbody = 10;
	float size = cbrt(rigidbodyMass) * 0.8f;
	float spawnX = -6;

	// Fait appara�tre les rigidbodys en ligne droite et les attaches via une tige
	for (int i = 0; i < nbrigidbody; i++)
	{
		spawnX += size;
		rigidbodys.push_back(Createrigidbody(scene, Vector3D(spawnX, 1, 0), Vector3D(2, 0, (rand() % 10 - 5) / 5.0f)));
		if(i > 0)
			contactSolver.generator.AddrigidbodyLinks(new RigidbodyRod(rigidbodys[i], rigidbodys[i - 1], size));
	}
	rigidbodys[nbrigidbody-1]->SetVelocity(Vector3D(20, 0, 0));
}

//##########
//#        #
//#  MAIN  #
//#        #
//##########

//supprime tous les �l�ments de la sc�ne
void ResetScene(Scene* scene)
{
	contactSolver.generator.RemoveAllrigidbodyLink();
	blobElements.clear();
	for (int i = Scene::mainScene->gameObjects.size() - 1; i >= 0; i--)
	{
		Scene::mainScene->RemoveRigidbody(Scene::mainScene->gameObjects[i]);
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
			if (event.key.keysym.sym == SDLK_SPACE) // Fait spawn un rigidbody en fonction de la position de la souris
			{
				int pixelMouseX, pixelMouseY;
				SDL_GetMouseState(&pixelMouseX, &pixelMouseY);
				float mouseX = pixelMouseX * 1.0f / SCREEN_WIDTH;
				float mouseY = 1 - (pixelMouseY * 1.0f / SCREEN_HEIGHT);
				float randZ = (-100 + rand() % 200) * randomZDirection * 0.01f;
				Createrigidbody(Scene::mainScene, Vector3D(0, 1, 0), Vector3D(-10 + mouseX * 20, mouseY * 15, randZ));
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

	ImGui::Text("Rigidbodys dans la scene: %d", Scene::mainScene->GetObjectsCount());
	ImGui::Text("Mise a jour de la physique: %.5fms", physicsUpdateTime);
	ImGui::Dummy(ImVec2(0.0f, 20.0f));
	ImGui::PushItemWidth(150);
	ImGui::SliderFloat("Masse des rigidbodys", &rigidbodyMass, 0.1, 10, "%.2f");
	ImGui::SliderFloat("Dispersion Z", &randomZDirection, 0, 5, "%.1f");

	ImGui::Dummy(ImVec2(0.0f, 20.0f));
	ImGui::PushItemWidth(150);

	ImGui::SliderFloat("Taille du lien", &rigidbodyLinkLength, 0, 5, "%.1f");

	
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

	Vector3D vTRS(5, 2, 3);
	Quaternion qTRS(1, 0, 1, 0);
	qTRS.Normalize();
	Matrix4 matTRS(vTRS, qTRS);

	std::cout << matTRS << std::endl;



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
				contactSolver.UpdateCollisions(Scene::mainScene, 4);
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