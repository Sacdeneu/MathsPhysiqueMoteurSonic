#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "../Physics/rigidbody.h"
#include "../Physics/forcesRegister.h"

class Scene
{
public:
	Scene(ForcesRegister* forcesRegister);
	int GetObjectsCount();
	void Addrigidbody(Rigidbody* p);
	void RemoveRigidbody(Rigidbody* p);
	void Update(float deltaTime);

	std::vector<Rigidbody*> gameObjects;
	ForcesRegister* forcesRegister;

	bool isPaused = false;

	static Scene* mainScene;
};
#endif

