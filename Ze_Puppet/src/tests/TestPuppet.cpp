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
#include <glm/gtx/string_cast.hpp>

namespace test {

	TestPuppet::TestPuppet(Camera* camera)
		: m_ClearColor{ 0.0f, 0.0f, 0.0f }, m_Lighting{ camera }, m_Camera{ camera }, m_Shader{ "res/shaders/Basic02.shader" },
		  m_Rotation{ 0.0f }, m_Translation{ 0.0f }, m_Pivot{ 0.0f }, m_Color{ 0.7f }
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

							m_Color = Head->GetColour();
							ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
							Head->SetColour(m_Color);

							m_quaternion = glm::quat(m_Rotation);
							m_Pivot = Head->GetPivot();
							Head->SetTransform(Head->GetTransform() * glm::translate(-m_Pivot) * glm::toMat4(m_quaternion) * glm::translate(m_Pivot));

							ImGui::TreePop();
						}
						else
						{
							ImGui::Text("Updating ...");
							ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

							m_Color = Neck->GetColour();
							ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
							Neck->SetColour(m_Color);

							m_quaternion = glm::quat(m_Rotation);
							m_Pivot = Neck->GetPivot();
							Neck->SetTransform(Neck->GetTransform() * glm::translate(-m_Pivot) * glm::toMat4(m_quaternion) * glm::translate(m_Pivot));
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

								m_Color = LeftHand->GetColour();
								ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
								LeftHand->SetColour(m_Color);

								m_quaternion = glm::quat(m_Rotation);
								m_Pivot = LeftHand->GetPivot();
								LeftHand->SetTransform(LeftHand->GetTransform() * glm::translate(-m_Pivot) * glm::toMat4(m_quaternion) * glm::translate(m_Pivot));

								ImGui::TreePop();
							}
							else
							{
								ImGui::Text("Updating ...");
								ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

								m_Color = LeftForearm->GetColour();
								ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
								LeftForearm->SetColour(m_Color);

								m_quaternion = glm::quat(m_Rotation);
								m_Pivot = LeftForearm->GetPivot();
								LeftForearm->SetTransform(LeftForearm->GetTransform() * glm::translate(-m_Pivot) * glm::toMat4(m_quaternion) * glm::translate(m_Pivot));
							}

							ImGui::TreePop();
						}
						else
						{
							ImGui::Text("Updating ...");
							ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

							m_Color = UpperLeftArm->GetColour();
							ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
							UpperLeftArm->SetColour(m_Color);

							m_quaternion = glm::quat(m_Rotation);
							m_Pivot = UpperLeftArm->GetPivot();
							UpperLeftArm->SetTransform(UpperLeftArm->GetTransform() * glm::translate(-m_Pivot) * glm::toMat4(m_quaternion) * glm::translate(m_Pivot));
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

								m_Color = RightHand->GetColour();
								ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
								RightHand->SetColour(m_Color);

								m_quaternion = glm::quat(m_Rotation);
								m_Pivot = RightHand->GetPivot();
								RightHand->SetTransform(RightHand->GetTransform() * glm::translate(-m_Pivot) * glm::toMat4(m_quaternion) * glm::translate(m_Pivot));

								ImGui::TreePop();
							}
							else
							{
								ImGui::Text("Updating ...");
								ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

								m_Color = RightForearm->GetColour();
								ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
								RightForearm->SetColour(m_Color);

								m_quaternion = glm::quat(m_Rotation);
								m_Pivot = RightForearm->GetPivot();
								RightForearm->SetTransform(RightForearm->GetTransform() * glm::translate(-m_Pivot) * glm::toMat4(m_quaternion) * glm::translate(m_Pivot));
							}

							ImGui::TreePop();
						}
						else
						{
							ImGui::Text("Updating ...");
							ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

							m_Color = UpperRightArm->GetColour();
							ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
							UpperRightArm->SetColour(m_Color);

							m_quaternion = glm::quat(m_Rotation);
							m_Pivot = UpperRightArm->GetPivot();
							UpperRightArm->SetTransform(UpperRightArm->GetTransform() * glm::translate(-m_Pivot) * glm::toMat4(m_quaternion) * glm::translate(m_Pivot));
						}

						ImGui::TreePop();
					}
					else
					{
						ImGui::Text("Updating ...");
						ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

						m_Color = Shoulders->GetColour();
						ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
						Shoulders->SetColour(m_Color);

						m_quaternion = glm::quat(m_Rotation);
						Shoulders->SetTransform(Shoulders->GetTransform() * glm::toMat4(m_quaternion));
					}

					ImGui::TreePop();
				}
				else if (ImGui::TreeNode("Hip"))
				{
					if (ImGui::TreeNode("Left Thigh"))
					{
						if (ImGui::TreeNode("LeftCalf"))
						{
							if (ImGui::TreeNode("LeftFoot"))
							{
								ImGui::Text("Updating ...");
								ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

								m_Color = LeftFoot->GetColour();
								ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
								LeftFoot->SetColour(m_Color);

								m_quaternion = glm::quat(m_Rotation);
								m_Pivot = LeftFoot->GetPivot();
								LeftFoot->SetTransform(LeftFoot->GetTransform()* glm::translate(-m_Pivot)* glm::toMat4(m_quaternion)* glm::translate(m_Pivot));

								ImGui::TreePop();
							}
							else
							{
								ImGui::Text("Updating ...");
								ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

								m_Color = LeftCalf->GetColour();
								ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
								LeftCalf->SetColour(m_Color);

								m_quaternion = glm::quat(m_Rotation);
								m_Pivot = LeftCalf->GetPivot();
								LeftCalf->SetTransform(LeftCalf->GetTransform()* glm::translate(-m_Pivot)* glm::toMat4(m_quaternion)* glm::translate(m_Pivot));
							}

							ImGui::TreePop();
						}
						else
						{
							ImGui::Text("Updating ...");
							ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

							m_Color = LeftThigh->GetColour();
							ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
							LeftThigh->SetColour(m_Color);

							m_quaternion = glm::quat(m_Rotation);
							m_Pivot = LeftThigh->GetPivot();
							LeftThigh->SetTransform(LeftThigh->GetTransform()* glm::translate(-m_Pivot)* glm::toMat4(m_quaternion)* glm::translate(m_Pivot));
						}

						ImGui::TreePop();
					}
					else if (ImGui::TreeNode("Right Thigh"))
					{
						if (ImGui::TreeNode("Right Calf"))
						{
							if (ImGui::TreeNode("Right Foot"))
							{
								ImGui::Text("Updating ...");
								ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

								m_Color = RightFoot->GetColour();
								ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
								RightFoot->SetColour(m_Color);

								m_quaternion = glm::quat(m_Rotation);
								m_Pivot = RightFoot->GetPivot();
								RightFoot->SetTransform(RightFoot->GetTransform() * glm::translate(-m_Pivot) * glm::toMat4(m_quaternion) * glm::translate(m_Pivot));

								ImGui::TreePop();
							}
							else
							{
								ImGui::Text("Updating ...");
								ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

								m_Color = RightCalf->GetColour();
								ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
								RightCalf->SetColour(m_Color);

								m_quaternion = glm::quat(m_Rotation);
								m_Pivot = RightCalf->GetPivot();
								RightCalf->SetTransform(RightCalf->GetTransform() * glm::translate(-m_Pivot) * glm::toMat4(m_quaternion) * glm::translate(m_Pivot));
							}

							ImGui::TreePop();
						}
						else
						{
							ImGui::Text("Updating ...");
							ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

							m_Color = RightThigh->GetColour();
							ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
							RightThigh->SetColour(m_Color);

							m_quaternion = glm::quat(m_Rotation);
							m_Pivot = RightThigh->GetPivot();
							RightThigh->SetTransform(RightThigh->GetTransform() * glm::translate(-m_Pivot) * glm::toMat4(m_quaternion) * glm::translate(m_Pivot));
						}

						ImGui::TreePop();
					}
					else
					{
						ImGui::Text("Updating ...");
						ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), -0.5f, 0.5f);

						m_Color = Hip->GetColour();
						ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
						Hip->SetColour(m_Color);

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

					m_Color = Torso->GetColour();
					ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
					Torso->SetColour(m_Color);

					m_quaternion = glm::quat(m_Rotation);
					Torso->SetTransform(glm::translate(Torso->GetTransform(), m_Translation) * glm::toMat4(m_quaternion));
				}

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}

		if (ImGui::Button("Reset Puppet"))
		{
			InitPuppet();
		}

		ImGui::ColorEdit3("Clear Color", m_ClearColor);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	void TestPuppet::BuildPuppet()
	{
		Torso = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
		Torso->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

			Shoulders = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
			Torso->AddChild(Shoulders);

				Neck = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
				Shoulders->AddChild(Neck);

					Head = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
					Neck->AddChild(Head);

				UpperLeftArm = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
				Shoulders->AddChild(UpperLeftArm);

					LeftForearm = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
					UpperLeftArm->AddChild(LeftForearm);

						LeftHand = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
						LeftForearm->AddChild(LeftHand);

				UpperRightArm = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
				Shoulders->AddChild(UpperRightArm);

					RightForearm = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
					UpperRightArm->AddChild(RightForearm);

						RightHand = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
						RightForearm->AddChild(RightHand);

			Hip = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
			Torso->AddChild(Hip);

				LeftThigh = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
				Hip->AddChild(LeftThigh);

					LeftCalf = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
					LeftThigh->AddChild(LeftCalf);

						LeftFoot = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
						LeftCalf->AddChild(LeftFoot);

				RightThigh = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
				Hip->AddChild(RightThigh);

					RightCalf = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
					RightThigh->AddChild(RightCalf);

						RightFoot = new SceneNode(&m_Objects[1], glm::vec3(0.7f, 0.7f, 0.7f));
						RightCalf->AddChild(RightFoot);

		InitPuppet();
	}

	void TestPuppet::InitPuppet()
	{
		Torso->SetModelScale(glm::vec3(1.0f, 2.0f, 0.5f));
		Torso->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

		Shoulders->SetModelScale(glm::vec3(1.35f, 0.25f, 0.25f));
		Shoulders->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, 0.0f)));

		Neck->SetModelScale(glm::vec3(0.15f, 0.3f, 0.15f));
		Neck->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.3f, 0.0f)));
		Neck->SetPivot(glm::vec3(0.0f, 0.5f, 0.0f));

		Head->SetModelScale(glm::vec3(0.5f, 0.5f, 0.5f));
		Head->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.6f, 0.0f)));
		Head->SetPivot(glm::vec3(0.0f, 0.4f, 0.0f));

		UpperLeftArm->SetModelScale(glm::vec3(0.25f, 1.2f, 0.25f));
		UpperLeftArm->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(1.25f, -1.1f, 0.0f)));
		UpperLeftArm->SetPivot(glm::vec3(0.0f, -1.1f, 0.0f));

		LeftForearm->SetModelScale(glm::vec3(0.2f, 1.0f, 0.2f));
		LeftForearm->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.9f, 0.0f)));
		LeftForearm->SetPivot(glm::vec3(0.0f, -0.95f, 0.0f));

		LeftHand->SetModelScale(glm::vec3(0.2f, 0.2f, 0.2f));
		LeftHand->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		LeftHand->SetPivot(glm::vec3(0.0f, -0.05f, 0.0f));

		UpperRightArm->SetModelScale(glm::vec3(0.25f, 1.2f, 0.25f));
		UpperRightArm->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, -1.1f, 0.0f)));
		UpperRightArm->SetPivot(glm::vec3(0.0f, -1.1f, 0.0f));

		RightForearm->SetModelScale(glm::vec3(0.2f, 1.0f, 0.2f));
		RightForearm->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.9f, 0.0f)));
		RightForearm->SetPivot(glm::vec3(0.0f, -0.95f, 0.0f));

		RightHand->SetModelScale(glm::vec3(0.2f, 0.2f, 0.2f));
		RightHand->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		RightHand->SetPivot(glm::vec3(0.0f, -0.05f, 0.0f));

		Hip->SetModelScale(glm::vec3(1.0f, 0.5f, 0.5f));
		Hip->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f)));

		LeftThigh->SetModelScale(glm::vec3(0.4f, 1.5f, 0.4f));
		LeftThigh->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -1.75f, 0.0f)));
		LeftThigh->SetPivot(glm::vec3(0.0f, -1.4f, 0.0f));

		LeftCalf->SetModelScale(glm::vec3(0.3f, 1.3f, 0.3f));
		LeftCalf->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.5f, 0.0f)));
		LeftCalf->SetPivot(glm::vec3(0.0f, -1.25f, 0.0f));

		LeftFoot->SetModelScale(glm::vec3(0.3f, 0.15f, 0.75f));
		LeftFoot->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.25f, 0.7f)));
		LeftFoot->SetPivot(glm::vec3(0.0f, 0.0f, 0.9f));

		RightThigh->SetModelScale(glm::vec3(0.4f, 1.5f, 0.4f));
		RightThigh->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -1.75f, 0.0f)));
		RightThigh->SetPivot(glm::vec3(0.0f, -1.4f, 0.0f));

		RightCalf->SetModelScale(glm::vec3(0.3f, 1.3f, 0.3f));
		RightCalf->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.5f, 0.0f)));
		RightCalf->SetPivot(glm::vec3(0.0f, -1.25f, 0.0f));

		RightFoot->SetModelScale(glm::vec3(0.3f, 0.15f, 0.75f));
		RightFoot->SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.25f, 0.7f)));
		RightFoot->SetPivot(glm::vec3(0.0f, 0.0f, 0.9f));
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