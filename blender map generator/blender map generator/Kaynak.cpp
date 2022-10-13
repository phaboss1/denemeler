#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class vec3
{
public:
	int x;
	int y;
	int z;
	vec3(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

int check(vec3 c, vec3 p)
{
	int x1 = pow((p.x - c.x), 2);
	int y1 = pow((p.y - c.y), 2);
	int z1 = pow((p.z - c.z), 2);

	// distance between the centre
	// and given point
	return (x1 + y1 + z1);
}

int main(void)
{
	vector<string> part0, part2;
	string line;
	ifstream MyReadFile("cubes.dae");
	int part = 0;
	while (getline(MyReadFile, line))
	{
		if (part == 0)
		{
			part0.push_back(line);
			if (line.find("<visual_scene") != string::npos)
				part = 1;
		}
		else if (part == 1)
		{
			if (line.find("</visual_scene>") != string::npos)
			{
				part = 2;
				part2.push_back(line);
			}
		}
		else if (part == 2)
		{
			part2.push_back(line);
		}
	}
	MyReadFile.close();

	// Write
	ofstream myfile;
	myfile.open("cubes2.dae");

	for (string line : part0)
		myfile << line << "\n";

	// Calculate
	vector<vec3> points;
	{
		vec3 c(0, 0, 0);

		int cubeSize = 2;
		int cubeRadius = 8;
		int r = (cubeRadius + 1) * cubeSize;

		for (int z = r; z >= -r; z -= cubeSize)
		{
			for (int x = r; x >= -r; x -= cubeSize)
			{
				for (int y = r; y >= -r; y -= cubeSize)
				{
					vec3 p(x, y, z);

					int ans = check(c, p);

					if (ans == (r * r) || ans < (r * r)) // if on surface or inside
					{
						int r2 = r - cubeSize;

						if (!(ans== (r2 * r2) || ans < (r2 * r2))) // if on surface or inside
						{
							points.push_back(p);
						}
						
					}
				}
			}
		}
	}

	// Write points
	{
		int ctr = 0;
		for (vec3 p : points)
		{
			ctr++;
			myfile << "      <node id=\"Cube_" << to_string(ctr) << "\" name=\"Cube." << to_string(ctr) << "\" type=\"NODE\">\n";
			myfile << "        <scale sid=\"scale\">1 1 1</scale>\n";
			myfile << "        <rotate sid=\"rotationZ\">0 0 1 0</rotate>\n";
			myfile << "        <rotate sid=\"rotationY\">0 1 0 0</rotate>\n";
			myfile << "        <rotate sid=\"rotationX\">1 0 0 0</rotate>\n";
			myfile << "        <translate sid=\"location\">" << p.x << " " << p.y << " " << p.z << "</translate>\n";
			myfile << "        <instance_geometry url=\"#Cube-mesh\" name=\"Cube" << to_string(ctr) << "\">\n";
			myfile << "          <bind_material>\n";
			myfile << "            <technique_common>\n";
			myfile << "              <instance_material symbol=\"Material-material\" target=\"#Material-material\">\n";
			myfile << "                <bind_vertex_input semantic=\"UVMap\" input_semantic=\"TEXCOORD\" input_set=\"0\"/>\n";
			myfile << "              </instance_material>\n";
			myfile << "            </technique_common>\n";
			myfile << "          </bind_material>\n";
			myfile << "        </instance_geometry>\n";
			myfile << "      </node>\n";
		}
	}

	for (string line : part2)
		myfile << line << "\n";

	myfile.close();
}