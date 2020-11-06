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
#include "glm/gtc/type_ptr.hpp"

namespace test {

	TestPuppet::TestPuppet(Camera* camera)
		: m_ClearColor{ 0.0f, 0.0f, 0.0f }, m_Lighting{ camera }, m_Camera{ camera }, m_Shader{ "res/shaders/Basic02.shader" },
		  m_Rotation(0.0f), m_Translation(0.0f)
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

		BuildPuppet();
	}

	TestPuppet::~TestPuppet()
	{
		delete Torso;
	}

	void TestPuppet::OnUpdate(float deltaTime)
	{
		m_Lighting.UpdateShader();

		m_Shader.Bind();
		m_Shader.SetUniform3f("u_lightColor", m_Lighting.m_LightColor[0], m_Lighting.m_LightColor[1], m_Lighting.m_LightColor[2]);
		m_Shader.SetUniform3f("u_lightPos", m_Lighting.m_Position[0], m_Lighting.m_Position[1], m_Lighting.m_Position[2]);
		m_Shader.SetUniformMat4f("u_VP", m_Camera->GetViewProjection());
		m_Shader.SetUniformVec3f("u_viewPos", m_Camera->GetPosition());

		Torso->OnUpdate(deltaTime);

		m_Translation *= 0.0f;
		m_Rotation *= 0.0f;
	}

	void TestPuppet::OnRender()
	{
		m_Renderer.Clear(m_ClearColor);

		m_Lighting.Draw();

		m_Shader.Bind();
		DrawPuppet();
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
				if (ImGui::TreeNode("Shoulders"))
				{
					if (ImGui::TreeNode("Neck"))
					{
						if (ImGui::TreeNode("Head"))
						{
							ImGui::Text("Updating ...");
							ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

							m_quaternion = glm::quat(m_Rotation);
							Head->SetTransform(Head->GetTransform() * glm::toMat4(m_quaternion));

							ImGui::TreePop();
						}
						else
						{
							ImGui::Text("Updating ...");
							ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

							m_quaternion = glm::quat(m_Rotation);
							Neck->SetTransform(Neck->GetTransform() * glm::toMat4(m_quaternion));
						}

						ImGui::TreePop();
					}
					else if (ImGui::TreeNode("Upper Left Arm"))
					{
						if (ImGui::TreeNode("Left Forearm"))
						{
							if (ImGui::TreeNode("Left Hand"))
							{
								ImGui::Text("Updating ...");
								ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

								m_quaternion = glm::quat(m_Rotation);
								LeftHand->SetTransform(LeftHand->GetTransform() * glm::toMat4(m_quaternion));

								ImGui::TreePop();
							}
							else
							{
								ImGui::Text("Updating ...");
								ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

								m_quaternion = glm::quat(m_Rotation);
								LeftForearm->SetTransform(LeftForearm->GetTransform() * glm::toMat4(m_quaternion));
							}

							ImGui::TreePop();
						}
						else
						{
							ImGui::Text("Updating ...");
							ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

							m_quaternion = glm::quat(m_Rotation);
							UpperLeftArm->SetTransform(UpperLeftArm->GetTransform() * glm::toMat4(m_quaternion));
						}

						ImGui::TreePop();
					}
					else if (ImGui::TreeNode("Upper Right Arm"))
					{
						if (ImGui::TreeNode("Right Forearm"))
						{
							if (ImGui::TreeNode("Right Hand"))
							{
								ImGui::Text("Updating ...");
								ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

								m_quaternion = glm::quat(m_Rotation);
								RightHand->SetTransform(RightHand->GetTransform() * glm::toMat4(m_quaternion));

								ImGui::TreePop();
							}
							else
							{
								ImGui::Text("Updating ...");
								ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

								m_quaternion = glm::quat(m_Rotation);
								RightForearm->SetTransform(RightForearm->GetTransform() * glm::toMat4(m_quaternion));
							}

							ImGui::TreePop();
						}
						else
						{
							ImGui::Text("Updating ...");
							ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

							m_quaternion = glm::quat(m_Rotation);
							UpperRightArm->SetTransform(UpperRightArm->GetTransform() * glm::toMat4(m_quaternion));
						}

						ImGui::TreePop();
					}
					else
					{
						ImGui::Text("Updating ...");
						ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

						m_quaternion = glm::quat(m_Rotation);
						Shoulders->SetTransform(Shoulders->GetTransform() * glm::toMat4(m_quaternion));
					}

					ImGui::TreePop();
				}
				else if (ImGui::TreeNode("Hip"))
				{
					if (false)
					{

					}
					else
					{
						ImGui::Text("Updating ...");
						ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

						m_quaternion = glm::quat(m_Rotation);
						Hip->SetTransform(Hip->GetTransform() * glm::toMat4(m_quaternion));
					}

					ImGui::TreePop();
				}
				else
				{
					ImGui::Text("Updating ...");
					ImGui::SliderFloat3("Translation", glm::value_ptr(m_Translation), -0.5f, 0.5f);
					ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

					m_quaternion = glm::quat(m_Rotation);
					Torso->SetTransform(glm::translate(Torso->GetTransform(), m_Translation) * glm::toMat4(m_quaternion));
				}

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}

		ImGui::ColorEdit3("Clear Color", m_ClearColor);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	void TestPuppet::BuildPuppet()
	{
		Torso = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
		Torso->SetModelScale(glm::vec3(1.0f, 2.0f, 0.5f));
		Torso->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

			Shoulders = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
			Shoulders->SetModelScale(glm::vec3(1.35f, 0.25f, 0.25f));
			Shoulders->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, 0.0f)));
			Torso->AddChild(Shoulders);

				Neck = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
				Neck->SetModelScale(glm::vec3(0.15f, 0.3f, 0.15f));
				Neck->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.3f, 0.0f)));
				Shoulders->AddChild(Neck);

					Head = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
					Head->SetModelScale(glm::vec3(0.5f, 0.5f, 0.5f));
					Head->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.6f, 0.0f)));
					Neck->AddChild(Head);

				UpperLeftArm = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
				UpperLeftArm->SetModelScale(glm::vec3(0.25f, 1.2f, 0.25f));
				UpperLeftArm->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(1.25f, -1.1f, 0.0f)));
				Shoulders->AddChild(UpperLeftArm);

					LeftForearm = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
					LeftForearm->SetModelScale(glm::vec3(0.2f, 1.0f, 0.2f));
					LeftForearm->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.9f, 0.0f)));
					UpperLeftArm->AddChild(LeftForearm);

						LeftHand = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
						LeftHand->SetModelScale(glm::vec3(0.2f, 0.2f, 0.2f));
						LeftHand->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
						LeftForearm->AddChild(LeftHand);

				UpperRightArm = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
				UpperRightArm->SetModelScale(glm::vec3(0.25f, 1.2f, 0.25f));
				UpperRightArm->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, -1.1f, 0.0f)));
				Shoulders->AddChild(UpperRightArm);

					RightForearm = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
					RightForearm->SetModelScale(glm::vec3(0.2f, 1.0f, 0.2f));
					RightForearm->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.9f, 0.0f)));
					UpperRightArm->AddChild(RightForearm);

						RightHand = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
						RightHand->SetModelScale(glm::vec3(0.2f, 0.2f, 0.2f));
						RightHand->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
						RightForearm->AddChild(RightHand);

			Hip = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
			Hip->SetModelScale(glm::vec3(1.0f, 0.5f, 0.5f));
			Hip->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f)));
			Torso->AddChild(Hip);
	}

	void TestPuppet::DrawPuppet()
	{
		DrawNode(Torso);
	}

	void TestPuppet::DrawNode(SceneNode* sn)
	{
		glm::mat4 transform = sn->GetWorldTransform() * glm::scale(sn->GetModelScale());
		m_Shader.SetUniformMat4f("u_model", transform);
		m_Shader.SetUniformVec3f("u_objectColor", sn->GetColour());
		sn->Draw(m_Shader);

		for (std::vector<SceneNode*>::const_iterator it = sn->GetChildIteratorBegin(); it != sn->GetChildIteratorEnd(); ++it)
		{
			DrawNode(*it);
		}
	}

}