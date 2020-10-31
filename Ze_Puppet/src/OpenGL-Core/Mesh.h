#pragma once

#include <string>
#include <vector>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include "Renderer.h"

class Mesh
{
private:
	std::string m_name;
	std::vector<float> m_vertices;
	std::vector<float> m_normals;
	std::vector<unsigned int> m_indices;

	VertexArray m_va;
	VertexBuffer m_vb, m_vnb;
	VertexBufferLayout m_layout;
	IndexBuffer m_ib;

	Renderer m_renderer;
public:
	Mesh(const std::string& name, const std::vector<float>& vertices, const std::vector<float>& normals, const std::vector<unsigned int>& indices);

	inline std::string GetName() const { return m_name; }

	void Setup();
	void Draw(Shader& shader);
};