#include "scene.h"
#include "../physics/plane.h"

Scene* Scene::mainScene = NULL;

Scene::Scene(ForcesRegister* forcesRegister)
{
	this->forcesRegister = forcesRegister;

	Rigidbody* ground = new Rigidbody(Vector3D(10, -10.5f, 0), 1);
	ground->SetStatic();
	ground->AddPrimitive(new Plane());
	gameObjects.push_back(ground);

	//spawn
	AddCubeToMap(Vector3D(0, -5.5f, 0), Vector3D(8, 10, 8), 0);
	AddCubeToMap(Vector3D(0, -0.5f, 0), Vector3D(8.5f, 0.5f, 8.5f), 1);
	//sol
	//AddCubeToMap(Vector3D(10, -10.5f, 0), Vector3D(40, 1, 20), 1);
	//escalier
	AddCubeToMap(Vector3D(5, -6.5f, 0), Vector3D(2, 8, 6), 0);
	AddCubeToMap(Vector3D(5.125f, -2.25f, 0), Vector3D(2.25f, 0.5f, 6.5f), 1);
	AddCubeToMap(Vector3D(7, -7.5f, 0), Vector3D(2, 6, 6), 0);
	AddCubeToMap(Vector3D(7.125f, -4.25f, 0), Vector3D(2.25f, 0.5f, 6.5f), 1);
	AddCubeToMap(Vector3D(9, -8.5f, 0), Vector3D(2, 4, 6), 0);
	AddCubeToMap(Vector3D(9.125f, -6.25f, 0), Vector3D(2.25f, 0.5f, 6.5f), 1);
	AddCubeToMap(Vector3D(11, -9.5f, 0), Vector3D(2, 2, 6), 0);
	AddCubeToMap(Vector3D(11.125f, -8.25f, 0), Vector3D(2.25f, 0.5f, 6.5f), 1);
	//murs
	AddCubeToMap(Vector3D(-10.5f, -12, 0), Vector3D(1, 10, 20), 0);
	AddCubeToMap(Vector3D(30.5f, -12, 0), Vector3D(1, 10, 20), 0);
	AddCubeToMap(Vector3D(10, -12, 10.5f), Vector3D(42, 10, 1), 0);
	AddCubeToMap(Vector3D(10, -12, -10.5f), Vector3D(42, 10, 1), 0);
	//oob
	/*
	AddCubeToMap(Vector3D(-19.5f, -7.5f, 0), Vector3D(20, 0.5f, 100), 1);
	AddCubeToMap(Vector3D(39.5f, -7.5f, 0), Vector3D(20, 0.5f, 100), 1);
	AddCubeToMap(Vector3D(10, -7.5f, 29.5f), Vector3D(40, 0.5f, 40), 1);
	AddCubeToMap(Vector3D(10, -7.5f, -29.5f), Vector3D(40, 0.5f, 40), 1);
	*/
}

void Scene::AddCubeToMap(Vector3D position, Vector3D scale, int textureID)
{
	AABB aabb(position, scale, textureID);
	map.push_back(aabb);
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
