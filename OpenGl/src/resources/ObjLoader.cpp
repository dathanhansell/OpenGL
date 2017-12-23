#include "ObjLoader.h"

using namespace std;
namespace MGLE {
	cModel ObjLoader::LoadOBJ(tString asFileName) {

		vector< unsigned int > vertexIndices, uvIndices, normalIndices;
		vector< Vector3 > temp_vertices;
		vector< Vector2 > temp_uvs;
		vector< Vector3 > temp_normals;
		asFileName = GetAbsolutePath() + asFileName;
		Log("Loading OBJ: %s\n", asFileName.c_str());
		ifstream obj;
		obj.open(asFileName);
		if (!obj.is_open()) {
			Error("Couldn't open: %s\n", asFileName.c_str());
			return cModel();
		}

		while (obj.peek() != EOF)
		{
			char line[128];
			obj.getline(line, sizeof(line));
			if (line[0] == 'v')
			{
				Vector3 vertex;
				int match = sscanf_s(line, "v %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if (line[0] == 'v' && line[1] == 'n')
			{
				Vector3 normal;
				int match = sscanf_s(line, "vn %f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (line[0] == 'v' && line[1] == 't')
			{
				Vector2 uv;
				int match = sscanf_s(line, "vt %f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
			else if (line[0] == 'f')
			{
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = sscanf_s(line, "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					int matches = sscanf_s(line, "f %d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]); //second scan// first scan of line
					if (matches != 6) {
						cout << "Unknown OBJ Loading Error :<" << endl;
						Error("Unknown OBJ Loading Error. %s", asFileName.c_str());
						return cModel();
					}

				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
		std::vector< Vector3 > vertices;
		std::vector< Vector2 > uvs;
		std::vector< Vector3 > normals;

		for (unsigned int i = 0; i < vertexIndices.size(); i++) {
			unsigned int vertexIndex = vertexIndices[i];
			Vector3 vertex = temp_vertices[vertexIndex - 1];
			vertices.push_back(vertex);
		}
		obj.close();
		Log( "Done!\n" );
		return cModel(vertices, uvs, normals);
	}

}