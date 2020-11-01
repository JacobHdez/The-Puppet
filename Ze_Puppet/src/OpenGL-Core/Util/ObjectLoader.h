#pragma once

#include <string>
#include <vector>
#include "Mesh.h"

bool loadOBJ(const std::string& filepath, std::vector<Mesh>& Objects);

void getUniqueVertex(std::vector<Vertex>& vertices, const Vertex& vertex, unsigned int& index);