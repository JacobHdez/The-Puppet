#pragma once

#include <string>
#include <vector>

class Mesh
{
private:
	std::string m_name;
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
public:
	Mesh(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

	inline std::string GetName() const { return m_name; }
	inline std::vector<float> GetVertices() const { return m_vertices; }
	inline std::vector<unsigned int> GetIndices() const { return m_indices; }
};