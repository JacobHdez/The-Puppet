#include "Mesh.h"

#include <string>
#include <vector>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include "Renderer.h"

Mesh::Mesh(const std::string& name, const std::vector<float>& vertices, const std::vector<float>& normals, const std::vector<unsigned int>& indices)
	: m_name(name), m_vertices(vertices), m_normals(normals), m_indices(indices) {}

void Mesh::Setup()
{
	m_va.Setup();

	m_vb.Setup(&m_vertices[0], m_vertices.size() * sizeof(float));
	//m_vnb.Setup(&m_normals[0], m_normals.size() * sizeof(float));

	m_layout.Push<float>(3);
	m_va.AddBuffer(m_vb, m_layout);
	/*m_layout.Push<float>(3);
	m_va.AddBuffer(m_vnb, m_layout);*/

	m_ib.Setup(&m_indices[0], m_indices.size());

	m_vb.Unbind();
	//m_vnb.Unbind();
	m_va.Unbind();
	m_ib.Unbind();
}

void Mesh::Draw(Shader& shader)
{
	m_renderer.Draw(m_va, m_ib, shader);
}