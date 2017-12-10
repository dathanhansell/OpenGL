#include "Model.h"

Model::Model(std::vector< Vector3 > Vertices,
	std::vector< Vector2 > Uvs,
	std::vector< Vector3 > Normals)
{
	vertices = Vertices;
	uvs = Uvs;
	normals = Normals;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), &vertices[0], GL_STATIC_DRAW);
}

Model::Model()
{

}

Model::~Model()
{
}

tri::tri(Vector3 A, Vector3 B, Vector3 C) {
	a = A;
	b = B;
	c = C;
	normal = CalcNormal(a,b,c);
	/*
	GLuint VBOID;
	glGenBuffers(1, &VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri), this, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	GLuint IBOID;
	glGenBuffers(1, &IBOID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLushort), this, GL_STATIC_DRAW);
	*/
}
void tri::CalcNormal()
{
	Vector3 d1 = Vector3(b.x - a.x, b.y - a.y, b.z - a.z);
	Vector3 d2 = Vector3(c.x - a.x, c.y - a.y, c.z - a.z);
	normal = Vector3(d1.y * d2.z - d1.z * d2.y, d1.z * d2.x - d1.x * d2.z, d1.x * d2.y - d1.y * d2.x).normalized();
}
Vector3 tri::CalcNormal(tri tri)
{
	Vector3 d1 = Vector3(tri.b.x - tri.a.x, tri.b.y - tri.a.y, tri.b.z - tri.a.z);
	Vector3 d2 = Vector3(tri.c.x - tri.a.x, tri.c.y - tri.a.y, tri.c.z - tri.a.z);
	return Vector3(d1.y * d2.z - d1.z * d2.y, d1.z * d2.x - d1.x * d2.z, d1.x * d2.y - d1.y * d2.x).normalized();
}
Vector3 tri::CalcNormal(Vector3 a, Vector3 b, Vector3 c)
{
	Vector3 d1 = Vector3(b.x - a.x, b.y - a.y, b.z - a.z);
	Vector3 d2 = Vector3(c.x - a.x, c.y - a.y, c.z - a.z);
	return Vector3(d1.y * d2.z - d1.z * d2.y, d1.z * d2.x - d1.x * d2.z, d1.x * d2.y - d1.y * d2.x).normalized();
}
Vector3 tri::Center() {
	return Vector3((a.x+b.x+c.x)/3, (a.y + b.y + c.y) / 3, (a.z + b.z + c.z) / 3);
}
void tri::Draw() {
	
	glPushMatrix();
	glBegin(GL_LINES);
	glColor4f(normal.x + this->Center().x, normal.y + this->Center().y, normal.z + this->Center().z,1);
	glVertex3f(this->Center().x, this->Center().y, this->Center().z);
	glVertex3f(normal.x + this->Center().x, normal.y + this->Center().y, normal.z + this->Center().z);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor4f(0.7, 0.7, 0.7, 1);
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);
	glVertex3f(c.x, c.y, c.z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	
}