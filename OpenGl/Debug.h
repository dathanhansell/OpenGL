#pragma once
#include "stdafx.h"
#include <gl\glut.h>
class Debug
{
public:
	static void DrawCardWireSphere(Vector3 p, float size = 1, int verts = 24);
	static void DrawWireSphere(Vector3 p, float size = 1, Vector3 color = { 1.0f,1.0f,1.0f }, int verts = 24);
	static void DrawAxes(Vector3 p);
};

