#include "Window.h"

void Reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(90.0f, (GLfloat)w / h, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
}
void Window::Init() {
	std::cout << "Creating Window..." << std::endl;
	width = 1280;
	height = 720;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) / 2,(glutGet(GLUT_SCREEN_HEIGHT) - height) / 2);
	glutCreateWindow("Game");
	glutReshapeFunc(Reshape);
}
void Window::ResetWindow() {
	glutReshapeWindow(width, height);
	glutPositionWindow(0, 0);
}
Window::Window() {
	Init();
}
Window::~Window() {
	glutDestroyWindow(0);
}
int Window::GetHeight() {
	return height;
}

int Window::GetWidth() {
	return width;
}