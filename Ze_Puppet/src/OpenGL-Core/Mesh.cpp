#include "Mesh.h"

#include <string>
#include <vector>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include "Renderer.h"

Mesh::Mesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
	: m_name(name), m_vertices(vertices), m_indices(indices) {}

void Mesh::Setup()
{
	m_va.Setup();

	m_vb.Setup(&m_vertices[0], m_vertices.size() * sizeof(Vertex));

	m_layout.Push<float>(3);
	m_layout.Push<float>(3);
	m_va.AddBuffer(m_vb, m_layout);

	m_ib.Setup(&m_indices[0], m_indices.size());

	m_vb.Unbind();
	m_va.Unbind();
	m_ib.Unbind();
}

void Mesh::Draw(Shader& shader)
{
	m_renderer.Draw(m_va, m_ib, shader);
}

bool operator==(const Vertex& lVertex, const Vertex& rVertex)
{
	if (lVertex.x == rVertex.x && lVertex.y == rVertex.y && lVertex.z == rVertex.z && lVertex.nx == rVertex.nx && lVertex.ny == rVertex.ny && lVertex.nz == rVertex.nz)
		return true;
	return false;
}
