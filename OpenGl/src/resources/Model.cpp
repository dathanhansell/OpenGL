#include "Model.h"
namespace MGLE {
	cModel::cModel(std::vector< Vector3 > Vertices,
		std::vector< Vector2 > Uvs,
		std::vector< Vector3 > Normals)
	{
		vbo = 0;
		vertices = Vertices;
		uvs = Uvs;
		normals = Normals;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), &vertices[0], GL_STATIC_DRAW);
	}

	cModel::cModel()
	{

	}

	cModel::~cModel()
	{
	}

	void cModel::Draw() {
		//glUseProgram(shader);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
		glDisableVertexAttribArray(0);
	}

}