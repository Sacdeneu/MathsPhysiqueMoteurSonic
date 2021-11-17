#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "../Physics/rigidbody.h"
#include "../Physics/forcesRegister.h"
#include "../Physics/AABB.h"

class Scene
{
public:
	Scene(ForcesRegister* forcesRegister);
	int GetObjectsCount();
	void Addrigidbody(Rigidbody* p);
	void Removerigidbody(Rigidbody* p);
	void Update(float deltaTime);
	void AddCubeToMap(Vector3D position, Vector3D scale, int textureID);

	std::vector<Rigidbody*> gameObjects;
	std::vector<AABB> map; //liste de cubes formant la map
	ForcesRegister* forcesRegister;

	static Scene* mainScene;
};
#endif

