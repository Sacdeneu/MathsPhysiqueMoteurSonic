#include "scene.h"

Scene::Scene()
{
}

int Scene::GetObjectsCount()
{
	return gameObjects.size();
}

void Scene::AddParticle(Particle* p)
{
	gameObjects.push_back(p);
}

void Scene::RemoveParticle(Particle* p)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (&gameObjects[i] == &p) //je suis pas sur que cette comparaison fonctionne
		{
			gameObjects.erase(gameObjects.begin() + i);
			return;
		}
	}
}
