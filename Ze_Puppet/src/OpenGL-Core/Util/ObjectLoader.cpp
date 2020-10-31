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
	std::vector<unsigned int> indices;
	float x, y, z;
	unsigned int vInd, i;
	bool firstOBJ = true;
	unsigned int count = 0;

	while (getline(stream, line))
	{
		/*if (line.find("#") != std::string::npos);
		else if (line.find("s ") != std::string::npos);
		else if (line.find("vn ") != std::string::npos);*/
		if (line.find("o ") != std::string::npos)
		{
			if (firstOBJ)
			{
				firstOBJ = false;
			}
			else
			{
				Objects.push_back(Mesh(name, position, indices));
				count += position.size() / 3.0f;
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
		else if (line.find("f ") != std::string::npos)
		{
			ss << line;
			ss.ignore(line.size(), ' ');

			for (i = 0; i < 3; ++i)
			{
				ss >> vInd;
				ss.ignore(line.size(), ' ');
				vInd -= 1 + count;
				indices.push_back(vInd);
			}
		}

		ss.str("");
		ss.clear();
	}
	Objects.push_back(Mesh(name, position, indices));

	stream.close();
	return true;
}
