#pragma once

#include "glm/glm.hpp"

class Camera
{
private:
	glm::mat4 m_Perspective;
	glm::vec3 m_Position;
	glm::vec3 m_Right;
	glm::vec3 m_Up;

	float FoV;
	float Aspect;
	float Near;
	float Far;

	float yaw = -90.0f;
	float pitch = 0.0f;

	float speed;
public:
	Camera();
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);

	glm::mat4 GetViewProjection();

	void ProcessKeyboard(unsigned int key);
	void ProcessMouseMovement(float xoffset, float yoffset);
	void ProcessMouseScroll(float xoffset, float yoffset);
};