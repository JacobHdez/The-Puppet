#pragma once

#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "glm/glm.hpp"

class Lighting
{
private:
	std::vector<Mesh> m_Object;
	Camera* m_Camera;
	Shader m_Shader;

	glm::mat4 m_Model;
public:
	float m_LightColor[3];
	float m_Position[3];

	Lighting(Camera* camera);

	void Setup();
	void Draw();
	void UpdateModel();
	void UpdateShader();
};