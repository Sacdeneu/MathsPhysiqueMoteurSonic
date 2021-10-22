#include "scene.h"

Scene* Scene::mainScene = NULL;

Scene::Scene(ForcesRegister* forcesRegister)
{
	this->forcesRegister = forcesRegister;

	AddCubeToMap(Vector3D(0, -5, 0), Vector3D(8, 10, 8));
	AddCubeToMap(Vector3D(10, -10.5f, 0), Vector3D(40, 1, 20));
	AddCubeToMap(Vector3D(5, -6, 0), Vector3D(2, 8, 6));
	AddCubeToMap(Vector3D(7, -7, 0), Vector3D(2, 6, 6));
	AddCubeToMap(Vector3D(9, -8, 0), Vector3D(2, 4, 6));
	AddCubeToMap(Vector3D(11, -9, 0), Vector3D(2, 2, 6));
	AddCubeToMap(Vector3D(-10.5f, -10, 0), Vector3D(1, 4, 20));
	AddCubeToMap(Vector3D(30.5f, -10, 0), Vector3D(1, 4, 20));
	AddCubeToMap(Vector3D(10, -10, 10.5f), Vector3D(40, 4, 1));
	AddCubeToMap(Vector3D(10, -10, -10.5f), Vector3D(40, 4, 1));
}

void Scene::AddCubeToMap(Vector3D position, Vector3D scale)
{
	AABB aabb(position, scale);
	map.push_back(aabb);
}

int Scene::GetObjectsCount()
{
	return gameObjects.size();
}

void Scene::AddParticle(Particle* p)
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

void Scene::RemoveParticle(Particle* p)
{
	forcesRegister->DeleteParticle(p);
	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), p), gameObjects.end());
	delete p;
}
