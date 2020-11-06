#pragma once

#include "Test.h"

#include <vector>
#include <string>
#include "Mesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "Util/Camera.h"
#include "Util/Lighting.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "SceneNode.h"

namespace test {

	class TestPuppet : public Test
	{
	private:
		Renderer m_Renderer;
		float m_ClearColor[3];
		glm::vec3 m_Color;

		Lighting m_Lighting;
		Camera* m_Camera;
		Shader m_Shader;

		std::vector<Mesh> m_Objects; // Cube and Sphere

		// Nodes
		SceneNode* Torso;
			SceneNode* Shoulders;
				SceneNode* Neck;
					SceneNode* Head;
				SceneNode* UpperLeftArm;
					SceneNode* LeftForearm;
						SceneNode* LeftHand;
				SceneNode* UpperRightArm;
					SceneNode* RightForearm;
						SceneNode* RightHand;
			SceneNode* Hip;
				SceneNode* LeftThigh;
					SceneNode* LeftCalf;
						SceneNode* LeftFoot;
				SceneNode* RightThigh;
					SceneNode* RightCalf;
						SceneNode* RightFoot;
				

		glm::vec3 m_Rotation;
		glm::vec3 m_Translation;
		glm::quat m_quaternion;
		glm::vec3 m_Pivot;
	public:
		TestPuppet(Camera *camera);
		~TestPuppet();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

		void BuildPuppet();
		void InitPuppet();
		void DrawPuppet();
		void DrawNode(SceneNode* sn);
	};

}