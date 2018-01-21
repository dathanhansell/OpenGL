#pragma once
#include "stdafx.h"
#include <gl\glut.h>
#include "Maths.h"

	class Debug
	{
	public:
		static void DrawCardWireSphere(Vector3 p, float size = 1, int verts = 24, Vector3 angle = { 0,0,0 });
		static void DrawGrid(int size, Vector3 color = {.5f,.5f,.5f});
		static void DrawWireSphere(Vector3 p, float size = 1, Vector3 color = { 1.0f,1.0f,1.0f }, int verts = 24);
		static void DrawAxes(Vector3 p, Vector3 angle = { 0,0,0 });
		static void DrawWireCircle(Vector3 p, float size = 1, Vector3 color = { 1.0f,1.0f,1.0f }, int verts = 24);
		// d: x = length, y = height, z = width
		static void DrawWireBox(Vector3 p, Vector3 d, Vector3 color = { 1.0f,1.0f,1.0f });
	};

