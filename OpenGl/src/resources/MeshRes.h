#pragma once
#include <gl\glew.h>
#include <gl\glut.h>
#include <vector>
#include <map>
#include "Maths.h"
#include "LowLevelSystem.h"
#include "tString.h"


namespace MGLE {
	struct PackedVertex {
		Vector3 position;

		Vector3 normal;
		bool operator<(const PackedVertex that) const {
			return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
		};
	};
	struct MeshData {
		MeshData() {
		}

		MeshData(std::vector< Vector3 > Vertices,

		std::vector< Vector3 > Normals) {
			vertices = Vertices;  normals = Normals;
		}
		MeshData(std::vector< Vector3 > Vertices,

			std::vector< Vector3 > Normals,
			std::vector<unsigned short> Indices) {
			vertices = Vertices;  normals = Normals; indices = Indices;
		}
		std::vector< Vector3 > vertices;
		std::vector< Vector3 > normals;
		std::vector<unsigned short> indices;
	};
	class cMeshRes {
		bool is_near(float v1, float v2);
		bool cMeshRes::getSimilarVertexIndex_fast(
			PackedVertex & packed,
			std::map<PackedVertex, unsigned short> & VertexToOutIndex,
			unsigned short & result
		);
		MeshData indexVBO(MeshData in);
		void cMeshRes::AddData(MeshData data);
	public:
		cMeshRes();
		~cMeshRes();
		MeshData mData;
		GLuint vbo, nbo, ebo;
		void LoadOBJ(tString asFileName);
	};
}
