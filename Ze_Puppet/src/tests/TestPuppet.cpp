#include "TestPuppet.h"

#include <iostream>
#include <string>
#include <vector>
#include "Util/ObjectLoader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"

namespace test {

	TestPuppet::TestPuppet(const std::string& filepath, Camera* camera)
		: m_ClearColor{ 0.0f, 0.0f, 0.0f }, m_ObjectColor{ 0.7f, 0.7f, 0.7f }, m_LightColor{ 1.0f, 1.0f, 1.0f },
		  m_Shader("res/shaders/Basic02.shader"), m_LightShader("res/shaders/Lighting.shader"),
		  m_Camera(camera)
	{
		if (!loadOBJ(filepath, m_Objects))
		{
			std::cout << "[-] Object error" << std::endl;
			exit(1);
		}
		for (auto& it : m_Objects)
			it.Setup();

		m_LightShader.Bind();
		m_LightShader.SetUniform4f("u_lightColor", m_LightColor[0], m_LightColor[1], m_LightColor[2], 1.0f);
		m_LightShader.SetUniformMat4f("u_MVP", m_Camera->GetViewProjection());

		m_Shader.Bind();
		m_Shader.SetUniform3f("u_objectColor", m_ObjectColor[0], m_ObjectColor[1], m_ObjectColor[2]);
		m_Shader.SetUniform3f("u_lightColor", m_LightColor[0], m_LightColor[1], m_LightColor[2]);
		m_Shader.SetUniform3f("u_lightPos", 5.0f, 5.0f, 5.0f);
		m_Shader.SetUniformMat4f("u_VP", m_Camera->GetViewProjection());
		m_Shader.SetUniformMat4f("u_model", glm::mat4(1.0f));
		m_Shader.SetUniformVec3f("u_viewPos", m_Camera->GetPosition());

		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glDepthFunc(GL_LESS));
	}

	TestPuppet::~TestPuppet()
	{
	}

	void TestPuppet::OnUpdate(float deltaTime)
	{
		m_Shader.Bind();
		m_Shader.SetUniform3f("u_objectColor", m_ObjectColor[0], m_ObjectColor[1], m_ObjectColor[2]);
		m_Shader.SetUniform3f("u_lightColor", m_LightColor[0], m_LightColor[1], m_LightColor[2]);
		//m_Shader.SetUniform3f("u_lightPos", 5.0f, 5.0f, 5.0f);
		m_Shader.SetUniformMat4f("u_VP", m_Camera->GetViewProjection());
		//m_Shader.SetUniformMat4f("u_model", glm::mat4(1.0f));
		m_Shader.SetUniformVec3f("u_viewPos", m_Camera->GetPosition());
	}

	void TestPuppet::OnRender()
	{
		m_Renderer.Clear(m_ClearColor);

		for (auto& it : m_Objects)
			it.Draw(m_Shader);
	}

	void TestPuppet::OnImGuiRender()
	{
		ImGui::Begin("The Puppet");

		ImGui::ColorEdit3("Clear Color", m_ClearColor);
		ImGui::ColorEdit3("Object Color", m_ObjectColor);
		ImGui::ColorEdit3("Light Color", m_LightColor);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

}