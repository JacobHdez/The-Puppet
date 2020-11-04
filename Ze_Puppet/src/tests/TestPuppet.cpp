#include "TestPuppet.h"

#include <iostream>
#include <string>
#include <vector>
#include "Util/ObjectLoader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

namespace test {

	TestPuppet::TestPuppet(Camera* camera)
		: m_ClearColor{ 0.0f, 0.0f, 0.0f }, m_Lighting{ camera }, m_Camera{ camera }, m_Shader{ "res/shaders/Basic02.shader" }
	{
		if (!loadOBJ("res/objects/cube.obj", m_Objects))
		{
			std::cout << "[-] Object error" << std::endl;
			exit(1);
		}
		if (!loadOBJ("res/objects/sphere.obj", m_Objects))
		{
			std::cout << "[-] Object error" << std::endl;
			exit(1);
		}

		for (auto& it : m_Objects)
			it.Setup();

		m_Lighting.Setup();

		m_Shader.Bind();
		m_Shader.SetUniform3f("u_lightColor", m_Lighting.m_LightColor[0], m_Lighting.m_LightColor[1], m_Lighting.m_LightColor[2]);
		m_Shader.SetUniform3f("u_lightPos", m_Lighting.m_Position[0], m_Lighting.m_Position[1], m_Lighting.m_Position[2]);
		m_Shader.SetUniform3f("u_objectColor", 0.7f, 0.7f, 0.7f);
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
		m_Lighting.UpdateShader();

		m_Shader.Bind();
		m_Shader.SetUniform3f("u_lightColor", m_Lighting.m_LightColor[0], m_Lighting.m_LightColor[1], m_Lighting.m_LightColor[2]);
		m_Shader.SetUniform3f("u_lightPos", m_Lighting.m_Position[0], m_Lighting.m_Position[1], m_Lighting.m_Position[2]);
		m_Shader.SetUniformMat4f("u_VP", m_Camera->GetViewProjection());
		m_Shader.SetUniformVec3f("u_viewPos", m_Camera->GetPosition());

		//m_Shader.SetUniform3f("u_objectColor", m_ObjectColor[0], m_ObjectColor[1], m_ObjectColor[2]);
		//m_Shader.SetUniformMat4f("u_model", glm::mat4(1.0f));
	}

	void TestPuppet::OnRender()
	{
		m_Renderer.Clear(m_ClearColor);

		m_Lighting.Draw();

		for (auto& it : m_Objects)
			it.Draw(m_Shader);
	}

	void TestPuppet::OnImGuiRender()
	{
		ImGui::Begin("Hierarchy");

		if (ImGui::TreeNode("Lighting"))
		{
			ImGui::SliderFloat3("Position", m_Lighting.m_Position, -10.0f, 10.0f);
			ImGui::ColorEdit3("Light Color", m_Lighting.m_LightColor);
			m_Lighting.UpdateModel();

			ImGui::TreePop();
		}
		if (ImGui::TreeNode("The Puppet"))
		{
			if (ImGui::TreeNode("Torso"))
			{
				if (ImGui::TreeNode("Hombros"))
				{
					ImGui::TreePop();
				}
				else if (ImGui::TreeNode("Cadera"))
				{
					ImGui::TreePop();
				}
				else
				{
					ImGui::Text("Updating ...");
					/*ImGui::SliderFloat3("Scaling", m_root.m_Scaling, 0.0f, 5.0f);
					ImGui::SliderFloat3("Rotation", m_root.m_Rotation, -180.0f, 180.0f);
					ImGui::SliderFloat3("Translation", m_root.m_Translation, -10.0f, 10.0f);*/
				}

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}

		ImGui::ColorEdit3("Clear Color", m_ClearColor);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

}