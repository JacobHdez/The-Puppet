#include "TestPuppet.h"

#include <iostream>
#include <string>
#include <vector>
#include "Util/ObjectLoader.h"
#include "Mesh.h"

namespace test {

	TestPuppet::TestPuppet(const std::string& filepath)
	{
		if (!loadOBJ(filepath, m_objects))
		{
			std::cout << "[-] Object error" << std::endl;
			exit(1);
		}

		for (auto& it : m_objects)
			it.Setup();
	}

	TestPuppet::~TestPuppet()
	{
	}

	void TestPuppet::OnUpdate(float deltaTime)
	{
	}

	void TestPuppet::OnRender(Shader& shader)
	{
		for (auto& it : m_objects)
			it.Draw(shader);
	}

	void TestPuppet::OnImGuiRender()
	{
	}

}