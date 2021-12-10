#include "scene.h"
#include "../physics/plane.h"
#include "../physics/box.h"

Scene* Scene::mainScene = NULL;

Scene::Scene(ForcesRegister* forcesRegister)
{
	this->forcesRegister = forcesRegister;

	Rigidbody* grass = new Rigidbody();
	grass->SetStatic();
	grass->renderingType = RenderingType::grass;
	grass->AddPrimitive(new Plane(Vector3D(0, 1, 0), -10)); //sol
	grass->AddPrimitive(new Box(Vector3D(0, -0.5f, 0), Vector3D(4.25f, 0.25f, 4.25f))); //plateforme de spawn
	for (int step = 0; step < 4; step++) //escalier
	{
		grass->AddPrimitive(new Box(Vector3D(5.125f + step * 2, -2.25f - step * 2, 0), Vector3D(1.125f, 0.25f, 3.25f)));
	}
	gameObjects.push_back(grass);

	Rigidbody* dirt = new Rigidbody();
	dirt->SetStatic();
	dirt->renderingType = RenderingType::dirt;
	dirt->AddPrimitive(new Box(Vector3D(0, -5.5f, 0), Vector3D(4, 5, 4))); //plateforme de spawn
	for (int step = 0; step < 4; step++) //escalier
	{
		dirt->AddPrimitive(new Box(Vector3D(5 + step * 2, -6.5f - step, 0), Vector3D(1, 4 - step, 3)));
	}
	gameObjects.push_back(dirt);
}

int Scene::GetObjectsCount()
{
	return gameObjects.size();
}

void Scene::Addrigidbody(Rigidbody* p)
{
	gameObjects.push_back(p);
}

void Scene::Update(float dt)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update(dt);
	}
}

void Scene::RemoveRigidbody(Rigidbody* p)
{
	forcesRegister->Deleterigidbody(p);
	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), p), gameObjects.end());
	delete p;
}
