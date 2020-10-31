#include "Mesh.h"

#include <string>
#include <vector>

Mesh::Mesh(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
{
	m_name = name;
	m_vertices = vertices;
	m_indices = indices;
}