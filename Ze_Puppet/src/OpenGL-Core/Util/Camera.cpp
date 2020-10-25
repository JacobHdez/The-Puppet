#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include "KeyCodes.h"

Camera::Camera()
	: FoV(glm::pi<float>() * 0.25f), Aspect(4.0f / 3.0f), Near(0.1f), Far(100.0f), speed(0.1f)
{
	//m_Perspective = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.0f);
	m_Perspective = glm::perspective(FoV, Aspect, Near, Far);
	m_Position = glm::vec3(0.0f, 0.0f, 5.0f);
	m_Right = glm::vec3(0.0f, 0.0f, -1.0f);
	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	: FoV(fov), Aspect(aspect), Near(zNear), Far(zFar), speed(0.1f)
{
	m_Perspective = glm::perspective(fov, aspect, zNear, zFar);
	m_Position = pos;
	m_Right = glm::vec3(0.0f, 0.0f, -1.0f);
	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::GetViewProjection()
{
	m_Perspective = glm::perspective(FoV, Aspect, Near, Far);
	return m_Perspective * glm::lookAt(m_Position, m_Position + m_Right, m_Up);
}

void Camera::ProcessKeyboard(unsigned int key)
{
	switch (key)
	{
	case KEY_W:
		m_Position += speed * m_Up;
		break;
	case KEY_S:
		m_Position -= speed * m_Up;
		break;
	case KEY_A:
		m_Position -= glm::normalize(glm::cross(m_Right, m_Up)) * speed;
		break;
	case KEY_D:
		m_Position += glm::normalize(glm::cross(m_Right, m_Up)) * speed;
		break;
	}
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
	yaw += xoffset * 0.1f;
	pitch += yoffset * 0.1f;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	m_Right = glm::normalize(direction);
}

void Camera::ProcessMouseScroll(float xoffset, float yoffset)
{
	m_Position += m_Right * (yoffset * speed);
	FoV += xoffset * speed;
}