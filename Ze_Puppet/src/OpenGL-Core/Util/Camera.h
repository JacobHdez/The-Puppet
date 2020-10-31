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

	bool press = false;

	float yaw = -90.0f;
	float pitch = 0.0f;

	float speed = 0.1f;
public:
	Camera();
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);

	glm::mat4 GetViewProjection();
	inline void SetAspect(float aspect) { Aspect = aspect; }

	void ProcessKeyboard(unsigned int key);
	void ProcessMouseMovement(float xoffset, float yoffset);
	void ProcessMouseScroll(float xoffset, float yoffset);
	void ProcessMouseButton(int button, int action);
};