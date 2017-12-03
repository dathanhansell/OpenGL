#include "stdafx.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glut.h>
Quaternion Q1;
int main(int argc, char** argv)
{
	Q1.Rotate(30, 60, 90);
	Q1.Print("Q1 ");
	Q1.Rotate(250, 124, 135);
	Q1.Print("Q1 ");


	SDL_Delay(30000);
	glutInit(&argc, argv);
	
	SDL_Quit();
	return 0;
}