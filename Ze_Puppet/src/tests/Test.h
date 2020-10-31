#pragma once

#include "Shader.h"

namespace test {

	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender(Shader& shader) {}
		virtual void OnImGuiRender() {}
	};

}