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

namespace test {

	class TestPuppet : public Test
	{
	private:
		Renderer m_Renderer;
		float m_ClearColor[3];

		Lighting m_Lighting;
		Camera* m_Camera;
		Shader m_Shader;

		std::vector<Mesh> m_Objects;
	public:
		TestPuppet(Camera *camera);
		~TestPuppet();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};

}