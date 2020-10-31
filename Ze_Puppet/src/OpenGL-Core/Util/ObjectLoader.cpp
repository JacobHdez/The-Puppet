#include "ObjectLoader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Mesh.h"

bool loadOBJ(const std::string& filepath, std::vector<Mesh>& Objects)
{
	std::ifstream stream(filepath);
	if (!stream.is_open())
	{
		std::cout << "[-] Error opening " << filepath << " file" << std::endl;
		return false;
	}

	std::string line;
	std::stringstream ss;

	std::string name;
	std::vector<float> position;
	std::vector<float> normals;
	std::vector<unsigned int> indices;
	float x, y, z;
	unsigned int vInd, vnInd, i;
	bool firstOBJ = true;
	unsigned int vCount = 0, vnCount = 0;

	while (getline(stream, line))
	{
		/*if (line.find("#") != std::string::npos);
		else if (line.find("s ") != std::string::npos);*/
		if (line.find("o ") != std::string::npos)
		{
			if (firstOBJ)
			{
				firstOBJ = false;
			}
			else
			{
				Objects.push_back(Mesh(name, position, normals, indices));
				vCount += position.size() / 3.0f;
				vnCount += normals.size() / 3.0f;
				position.clear();
				indices.clear();
			}
			name = line.substr(2);
		}
		else if (line.find("v ") != std::string::npos)
		{
			ss << line;
			ss.ignore(line.size(), ' ');
			ss >> x >> y >> z;
			position.push_back(x);
			position.push_back(y);
			position.push_back(z);
		}
		else if (line.find("vn ") != std::string::npos)
		{
			ss << line;
			ss.ignore(line.size(), ' ');
			ss >> x >> y >> z;
			normals.push_back(x);
			normals.push_back(y);
			normals.push_back(z);
		}
		else if (line.find("f ") != std::string::npos)
		{
			ss << line;
			ss.ignore(line.size(), ' ');

			for (i = 0; i < 3; ++i)
			{
				ss >> vInd;
				ss.ignore(line.size(), '/');
				ss.ignore(line.size(), '/');
				ss >> vnInd;
				vInd -= 1 + vCount;
				vnInd -= 1 + vnCount;
				indices.push_back(vInd);
				//indices.push_back(vnInd);
			}
		}

		ss.str("");
		ss.clear();
	}
	Objects.push_back(Mesh(name, position, normals, indices));

	stream.close();
	return true;
}
