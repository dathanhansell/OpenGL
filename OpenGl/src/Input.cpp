#include "Input.h"
#include <gl\glut.h>
#include <iostream>
using namespace std;
bool warper = true, warp = false;
void Init();
Input::Input() {
	Init();
}
Input::~Input() {

}
void KeyUp(unsigned char key, int X, int Y) 
{

}

void Key(unsigned char key, int X, int Y) 
{

}

void MousePassive(int X, int Y) 
{
	if (GetActiveWindow() == 00000000) return;
}
void Input::Init()
{
	cout << "Initializing Input Module..." << endl;
	glutPassiveMotionFunc(MousePassive);
	glutKeyboardFunc(Key);
	glutKeyboardUpFunc(KeyUp);
	cout << "Done!" << endl;
}
