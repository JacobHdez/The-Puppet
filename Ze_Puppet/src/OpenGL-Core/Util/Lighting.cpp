#include "Lighting.h"

#include <iostream>
#include "Util/ObjectLoader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Lighting::Lighting(Camera* camera)
	: m_Camera(camera), m_Shader("res/shaders/Lighting.shader"), m_LightColor{ 1.0f, 1.0f, 1.0f }, m_Position{ 5.0f, 5.0f, 5.0f }, m_Model(1.0f)
{
	if (!loadOBJ("res/objects/cube.obj", m_Object))
	{
		std::cout << "[-] Object error" << std::endl;
		exit(1);
	}
}

void Lighting::Setup()
{
	for (auto& it : m_Object)
		it.Setup();

	m_Shader.Bind();
	m_Shader.SetUniform4f("u_lightColor", m_LightColor[0], m_LightColor[1], m_LightColor[2], 1.0f);

	m_Model = glm::translate(m_Model, glm::vec3(m_Position[0], m_Position[1], m_Position[2]));
	m_Model = glm::scale(m_Model, glm::vec3(0.1f));
	m_Shader.SetUniformMat4f("u_MVP", m_Camera->GetViewProjection() * m_Model);

	m_Shader.Unbind();
}

void Lighting::Draw()
{
	for (auto& it : m_Object)
		it.Draw(m_Shader);
}

void Lighting::UpdateModel()
{
	m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position[0], m_Position[1], m_Position[2]));
	m_Model = glm::scale(m_Model, glm::vec3(0.1f));
}

void Lighting::UpdateShader()
{
	m_Shader.Bind();
	m_Shader.SetUniform4f("u_lightColor", m_LightColor[0], m_LightColor[1], m_LightColor[2], 1.0f);
	m_Shader.SetUniformMat4f("u_MVP", m_Camera->GetViewProjection() * m_Model);
}