#include "Input.h"
#include <gl\glut.h>
#include "Display.h"
#include <iostream>
using namespace std;
bool warper = true, warp = false;
void Input::KeyUp(unsigned char key, int X, int Y) 
{
	Keys[key] = false;
}

void Input::Key(unsigned char key, int X, int Y) 
{
	Keys[key] = true;
	if (Input::Keys['q']) {
		if (warper) {
			warp = !warp;
		}
		warper = false;
	}
	else
	{
		warper = true;
	}
}

void Input::MousePassive(int X, int Y) 
{
	if (GetActiveWindow() == 00000000) return;
	mouse = Vector2( X ,Y ) - oldMouse;
	
	cam.rotation += {mouse.x, -mouse.y};
	//cam.rotation.print("Mouse: ");
	//if (warp) glutWarpPointer(Display::width / 2, Display::height / 2);
	oldMouse = Vector2(X, Y);
	
}
Camera Input::cam = { { 0,0 },{ 3,.7f,-3 } };
void Input::SetupInput()
{
	glutPassiveMotionFunc(MousePassive);
	glutKeyboardUpFunc(KeyUp);
	glutKeyboardFunc(Key);
}
bool Input::Keys[256];
Vector2 Input::mouse = Vector2::zero;
Vector2 Input::oldMouse = Vector2::zero;