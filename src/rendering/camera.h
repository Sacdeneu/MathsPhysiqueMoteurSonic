#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>

#include "shader.h"

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	Camera();
	void SetPosition(float x, float y, float z);
	void Update(float deltaTime);
	void SetMatrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	
	void UpdateKeyboardInput(char key, bool state);
	void UpdateMouseInput(float mouseX, float mouseY);

private:
	float moveX, moveY, rotX, rotY;
};
#endif

