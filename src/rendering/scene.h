#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "../Physics/Particle.h"

class Scene
{
public:
	Scene();
	int GetObjectsCount();
	void AddParticle(Particle* p);
	void RemoveParticle(Particle* p);
	void Update(float deltaTime);

	std::vector<Particle*> gameObjects;
};
#endif

