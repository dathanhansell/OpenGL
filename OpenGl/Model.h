#pragma once
#include <vector>
#include "Maths.h"
#include <gl\glew.h>
class Model
{
public:
	GLuint vertexbuffer;
	std::vector< Vector3 > vertices;
	std::vector< Vector2 > uvs;
	std::vector< Vector3 > normals;
	Model(std::vector< Vector3 > Vertices,
	std::vector< Vector2 > Uvs,
	std::vector< Vector3 > Normals);
	Model();
	~Model();
};
struct tri{

	Vector3 a, b, c, normal;	
	tri(Vector3 A, Vector3 B, Vector3 C);
	void CalcNormal();
	static Vector3 CalcNormal(tri tri);
	static Vector3 CalcNormal(Vector3 a, Vector3 b, Vector3 c);
	void Draw();
	Vector3 Center();
};

