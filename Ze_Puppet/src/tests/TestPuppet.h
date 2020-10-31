#pragma once

#include "Test.h"

#include <vector>
#include <string>
#include "Mesh.h"

namespace test {

	class TestPuppet : public Test
	{
	private:

	public:
		std::vector<Mesh> m_objects;

		TestPuppet(const std::string& filepath);
		~TestPuppet();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};

}