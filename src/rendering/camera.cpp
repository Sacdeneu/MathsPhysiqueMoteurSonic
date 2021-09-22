#include "camera.h"
#include "renderer.h"

Camera::Camera()
{
	position = glm::vec3();
	rotX = 3.14159f;
	rotY = -0.15f;
	UpdateMouseInput(0, 0);
}

void Camera::SetPosition(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
}

void Camera::Update(float deltaTime)
{
	//position += glm::vec3(moveX * 5 * deltaTime, 0, -moveY * 5 * deltaTime);
	position += (forward * (moveY * 5 * deltaTime)) + (right * (moveX * 5 * deltaTime));
}

void Camera::SetMatrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	//direction de la camera
	view = glm::lookAt(position, position + forward, up);

	//perspective
	projection = glm::perspective(glm::radians(FOVdeg), (float)SCREEN_WIDTH / SCREEN_HEIGHT, nearPlane, farPlane);

	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.program, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::UpdateKeyboardInput(char key, bool state)
{
	if (key == 'z' || key == 'w') moveY = state ? 1 : 0;
	else if (key == 'q' || key == 'a') moveX = state ? -1 : 0;
	else if (key == 's') moveY = state ? -1 : 0;
	else if (key == 'd') moveX = state ? 1 : 0;
}

void Camera::UpdateMouseInput(float mouseX, float mouseY)
{

	float halfPi = 1.57079f;
	rotX += mouseX * 0.0012f;
	rotY += mouseY * 0.0012f;
	rotY = rotY > halfPi ? halfPi : rotY < -halfPi ? -halfPi : rotY;
	forward = glm::vec3(cos(rotY) * sin(rotX), sin(rotY), cos(rotY) * cos(rotX));
	right = glm::cross(forward, up);
	//up = glm::vec3(cos(rotY + piHalf) * sin(rotX), sin(rotY + piHalf), cos(rotY + piHalf) * cos(rotX));
}