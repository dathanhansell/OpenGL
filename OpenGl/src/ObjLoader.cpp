#include "ObjLoader.h"
#include <iostream>
#include <fstream>
#include "SDL.h"
#include <gl\glew.h>
#include <SDL_opengl.h>
#include "Model.h"
using namespace std;
Model ObjLoader::loadOBJ(const char * File) {
	int lines = 0;
	vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	vector< Vector3 > temp_vertices;
	vector< Vector2 > temp_uvs;
	vector< Vector3 > temp_normals;
	const char *path = new char[strlen((const char*)SDL_GetBasePath()) + strlen(File) + 1];
	strcpy((char*)path, SDL_GetBasePath());
	strcat((char*)path, File);
	cout << "Loading .obj: " << path << std::endl;
	ifstream obj;
	obj.open(path);

	delete path;
	if (!obj.is_open()) {
		const char *error;
		error = new char[strlen("Failure to open file : ") + strlen(SDL_GetBasePath()) + strlen(File) + strlen("\n") + 1];
		strcpy((char*)error, "Failure to open file: ");
		strcat((char*)error, SDL_GetBasePath());
		strcat((char*)error, File);
		strcat((char*)error, "\n");
		printf(error);
		delete error;
		return Model();
	}

	while (obj.peek() != EOF)
	{
		char line[128];
		obj.getline(line, sizeof(line));
		if (line[0] == 'v')
		{
			Vector3 vertex;
			int match = sscanf(line, "v %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (line[0] == 'v' && line[1] == 'n')
		{
			Vector3 normal;
			int match = sscanf(line, "vn %f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (line[0] == 'v' && line[1] == 't')
		{
			Vector2 uv;
			int match = sscanf(line, "vt %f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (line[0] == 'f')
		{
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				int matches = sscanf(line, "f %d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]); //second scan// first scan of line
				if (matches != 6) {
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OBJLoader Error", "OBJ ERROR :<", NULL);
					return Model();
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
	return Model(vertices, uvs, normals);
}
	