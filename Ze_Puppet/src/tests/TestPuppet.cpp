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
		//shader.Bind();

		/*GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		shader.SetUniform4f("u_Color", 0.8f, 0.8f, 0.8f, 1.0f);*/
		for (auto& it : m_objects)
			it.Draw(shader);

		/*GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);
		for (auto& it : m_objects)
			it.Draw(shader);*/
	}

	void TestPuppet::OnImGuiRender()
	{
	}

}