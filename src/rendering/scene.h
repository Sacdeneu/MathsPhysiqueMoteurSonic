#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "../Physics/Particle.h"
#include "../Physics/forcesRegister.h"
#include "../Physics/AABB.h"

class Scene
{
public:
	Scene(ForcesRegister* forcesRegister);
	int GetObjectsCount();
	void AddParticle(Particle* p);
	void RemoveParticle(Particle* p);
	void Update(float deltaTime);
	void AddCubeToMap(Vector3D position, Vector3D scale);

	std::vector<Particle*> gameObjects;
	std::vector<AABB> map; //liste de cubes formant la map
	ForcesRegister* forcesRegister;

	static Scene* mainScene;
};
#endif

