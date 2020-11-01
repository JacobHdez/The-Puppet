#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

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

	bool press = false;

	float yaw = -90.0f;
	float pitch = 0.0f;

	float speed = 0.1f;
public:
	Camera();
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);

	void SetAspect(float aspect);

	glm::mat4 GetViewProjection();
	glm::vec3 GetPosition();
	glm::mat4 GetView();
	glm::mat4 GetProjection();

	void ProcessKeyboard(unsigned int key);
	void ProcessMouseMovement(float xoffset, float yoffset);
	void ProcessMouseScroll(float xoffset, float yoffset);
	void ProcessMouseButton(int button, int action);
};