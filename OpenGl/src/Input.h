#pragma once
#include "Maths.h"
#include "Camera.h"
class Input
{
	
private:
	static Vector2 oldMouse;
	static void KeyUp(unsigned char key, int X, int Y);
	static void Key(unsigned char key, int X, int Y);
	static void MousePassive(int X, int Y);
public:
	static Camera cam;
	static bool Keys[256];
	static Vector2 mouse;
	static void SetupInput();
};

