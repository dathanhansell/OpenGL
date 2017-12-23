#pragma once
#include "MGLE.h"
namespace MGLE {
	class cModel
	{
	public:
		GLuint vbo;
		std::vector< Vector3 > vertices;
		std::vector< Vector2 > uvs;
		std::vector< Vector3 > normals;
		cModel(std::vector< Vector3 > Vertices,
			std::vector< Vector2 > Uvs,
			std::vector< Vector3 > Normals);
		cModel();
		~cModel();
		void Draw();
	};

}