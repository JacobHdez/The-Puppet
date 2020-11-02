#pragma once

#include "Test.h"

#include <vector>
#include <string>
#include "Mesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "Util/Camera.h"

namespace test {

	class TestPuppet : public Test
	{
	private:
		std::vector<Mesh> m_Objects;
		float m_ObjectColor[3];
		Shader m_Shader;

		float m_LightColor[3];
		Shader m_LightShader;

		float m_ClearColor[3];
		Renderer m_Renderer;
		Camera *m_Camera;
	public:
		TestPuppet(const std::string& filepath, Camera *camera);
		~TestPuppet();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};

}