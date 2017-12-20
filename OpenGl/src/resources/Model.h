#pragma once
#include "MGLE.h"
namespace MGLE {
	class Model
	{
	public:
		GLuint vbo;
		std::vector< Vector3 > vertices;
		std::vector< Vector2 > uvs;
		std::vector< Vector3 > normals;
		Model(std::vector< Vector3 > Vertices,
			std::vector< Vector2 > Uvs,
			std::vector< Vector3 > Normals);
		Model();
		~Model();
		void Draw();
	};

}