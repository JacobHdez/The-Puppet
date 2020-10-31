#pragma once

#include "Test.h"

#include <vector>
#include <string>
#include "Mesh.h"

namespace test {

	class TestPuppet : public Test
	{
	private:
		std::vector<Mesh> m_objects;
	public:
		TestPuppet(const std::string& filepath);
		~TestPuppet();

		void OnUpdate(float deltaTime) override;
		void OnRender(Shader& shader) override;
		void OnImGuiRender() override;
	};

}