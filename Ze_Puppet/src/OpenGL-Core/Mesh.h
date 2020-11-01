#pragma once

#include <string>
#include <vector>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include "Renderer.h"

struct Vertex
{
	float x, y, z;
	float nx, ny, nz;
};

bool operator == (const Vertex& lVertex, const Vertex& rVertex);

class Mesh
{
private:
	std::string m_name;
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;

	VertexArray m_va;
	VertexBuffer m_vb;
	VertexBufferLayout m_layout;
	IndexBuffer m_ib;

	Renderer m_renderer;
public:
	Mesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

	inline std::string GetName() const { return m_name; }

	void Setup();
	void Draw(Shader& shader);
};