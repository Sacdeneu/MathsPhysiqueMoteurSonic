#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "../Physics/Particle.h"
#include "../Physics/forcesRegister.h"

struct AABB //Axis Aligned Bounding Box
{
	Vector3D position;
	Vector3D scale;

	float GetMinX() { return position.x - scale.x * 0.5f; };
	float GetMaxX() { return position.x + scale.x * 0.5f; };
	float GetMinY() { return position.y - scale.y * 0.5f; };
	float GetMaxY() { return position.y + scale.y * 0.5f; };
	float GetMinZ() { return position.z - scale.z * 0.5f; };
	float GetMaxZ() { return position.z + scale.z * 0.5f; };
};

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

