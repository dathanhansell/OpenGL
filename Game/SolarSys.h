#pragma once
#include "stdafx.h"
#include <MGLE.h>
class Sys {
	

	Game* m_g;
	Vector3 pos = { 0,0,0 };
	float c;
	int w, h;
	void Planet(float rad, float radfromsun, float speed, Vector3 color);
public:
	Sys(Game* g);
	void Run();
};