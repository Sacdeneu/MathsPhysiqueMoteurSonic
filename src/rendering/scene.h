#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "../Physics/Particle.h"
#include "../Physics/forcesRegister.h"

class Scene
{
public:
	Scene(ForcesRegister* forcesRegister);
	int GetObjectsCount();
	void AddParticle(Particle* p);
	void RemoveParticle(Particle* p);
	void Update(float deltaTime);

	std::vector<Particle*> gameObjects;
	ForcesRegister* forcesRegister;

	static Scene* mainScene;
};
#endif

