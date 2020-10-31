#include "Mesh.h"

#include <string>
#include <vector>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include "Renderer.h"

Mesh::Mesh(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
{
	m_name = name;
	m_vertices = vertices;
	m_indices = indices;
}

void Mesh::Setup()
{
	m_vb.Setup(&m_vertices[0], m_vertices.size() * sizeof(float));

	m_layout.Push<float>(3);
	m_va.Setup();
	m_va.AddBuffer(m_vb, m_layout);

	m_ib.Setup(&m_indices[0], m_indices.size());

	m_vb.Unbind();
	m_vb.Unbind();
	m_ib.Unbind();
}

void Mesh::Draw(Shader& shader)
{
	m_renderer.Draw(m_va, m_ib, shader);
}