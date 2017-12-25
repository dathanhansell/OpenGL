#include "MeshRes.h"

using namespace std;
namespace MGLE {
	cMeshRes::cMeshRes()
	{

	}
	cMeshRes::~cMeshRes()
	{
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &nbo);
		glDeleteBuffers(1, &ebo);
	}
	void cMeshRes::LoadOBJ(tString asFileName) {

		vector< unsigned int > vertexIndices, normalIndices,uvIndices;
		vector< Vector3 > temp_vertices;
		vector< Vector2 > temp_uvs;
		vector< Vector3 > temp_normals;
		asFileName = GetAbsolutePath() + asFileName;
		Log("Loading OBJ: %s\n", asFileName.c_str());
		ifstream obj;
		obj.open(asFileName);
		if (!obj.is_open()) {
			FatalError("Couldn't open: %s\n", asFileName.c_str());
		}

		while (obj.peek() != EOF)
		{
			char line[128];
			obj.getline(line, sizeof(line));
			if (line[0] == 'v' && line[1] == 'n')
			{
				Vector3 normal;
				int match = sscanf_s(line, "vn %f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (line[0] == 'v')
			{
				Vector3 vertex;
				int match = sscanf_s(line, "v %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
				
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
						FatalError("Unknown OBJ Loading Error. %s", asFileName.c_str());
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
		Log("TEMP V Size: %i\n",temp_vertices.size());
		Log("TEMP i Size: %i\n", vertexIndices.size());
		MeshData out;
		Log("o V Size: %i\n", out.vertices.size());

		for (unsigned int i = 0; i<vertexIndices.size(); i++) {

			unsigned int vertexIndex = vertexIndices[i];
			unsigned int normalIndex = normalIndices[i];

			Vector3 vertex = temp_vertices[vertexIndex - 1];
			Vector3 normal = temp_normals[normalIndex - 1];

			out.vertices.push_back(vertex);
			out.normals.push_back(normal);
		}
		Log("O V Size: %i\n", out.vertices.size());


		obj.close();
		Log("Done Loading...\n");
		out = indexVBO(out);
		Log("I Size: %i\n", out.indices.size());
		AddData(out);
		
	}
	void cMeshRes::AddData(MeshData data) {
		vbo = 0;
		nbo = 0;
		mData = data;
		Log("V Size: %i\n", mData.vertices.size());
		Log("N Size: %i\n", mData.normals.size());
		Log("I Size: %i\n", mData.indices.size());
		for (int i = 0; i<(mData.vertices.size() - 1) / 2; ++i) {
			//swap(mData.vertices[i], mData.vertices[mData.vertices.size() - 2 - i]);
		}
		Log("V3: %i 3F: %i\n", mData.vertices.size() * sizeof(Vector3), mData.vertices.size() * 3 * sizeof(float));
		if (mData.vertices.size() > 0) {
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, mData.vertices.size() * sizeof(Vector3), &mData.vertices[0], GL_STATIC_DRAW);
		}
		
		else {
			Error("Model has no verts.");
		}
		if (mData.normals.size() > 0) {
			glGenBuffers(1, &nbo);
			glBindBuffer(GL_ARRAY_BUFFER, nbo);
			glBufferData(GL_ARRAY_BUFFER, mData.normals.size() * sizeof(Vector3), &mData.normals[0], GL_STATIC_DRAW);
		}
		else {
			Error("Model has no normals.");
		}
		for (int i = 0; i<(mData.indices.size() - 1)/ mData.indices.size(); i++) {
			//swap(mData.indices[i], mData.indices[mData.indices.size() - 2 - i]);
		}
		if (mData.indices.size() > 0) {
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mData.indices.size() * sizeof(unsigned short), &mData.indices[0], GL_STATIC_DRAW);
		}
		else {
			Error("Something went wrong with the indices.");
		}
		
	}
	bool cMeshRes::is_near(float v1, float v2) {
		return fabs(v1 - v2) < 0.01f;
	}
	bool cMeshRes::getSimilarVertexIndex_fast(
		PackedVertex & packed,
		std::map<PackedVertex, unsigned short> & VertexToOutIndex,
		unsigned short & result
	) {
		std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
		if (it == VertexToOutIndex.end()) {
			return false;
		}
		else {
			result = it->second;
			return true;
		}
	}

	MeshData cMeshRes::indexVBO(MeshData in) {
		Log("Indexing Model VBO...\n");
		std::map<PackedVertex, unsigned short> VertexToOutIndex;
		std::vector< Vector3 > out_vertices;
		std::vector< Vector2 > out_uvs;
		std::vector< Vector3 > out_normals;
		std::vector<unsigned short> out_indices;
		for (unsigned int i = 0; i<in.vertices.size(); i++) {
			
			if (in.vertices.size() == 0) {
				FatalError("Cannot index empty mesh!");
			}
			PackedVertex packed = { in.vertices[i], in.normals[i] };

			// Try to find a similar vertex in out_XXXX
			unsigned short index;
			bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);
			if (found) { // A similar vertex is already in the VBO, use it instead !

				out_indices.push_back(index);
			}
			else { // If not, it needs to be added in the output data.
				
				out_vertices.push_back(in.vertices[i]);
				//out_uvs.push_back(in.uvs[i]);
				out_normals.push_back(in.normals[i]);
				unsigned short newindex = (unsigned short)out_vertices.size() - 1;
				out_indices.push_back(newindex);
				
				VertexToOutIndex[packed] = newindex;
			}
		}
		Log("Indices: %i\n",out_indices.size());
		Log("Done!\n");
		return MeshData(out_vertices,out_normals, out_indices);
	}
}