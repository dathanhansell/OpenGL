#include "stdafx.h"
#include "GLWidget.h"


GLWidget::GLWidget(QWidget *parent)
	: QGLWidget(parent)
{
	
}
void GLWidget::resizeGL(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}
void GLWidget::initializeGL() {
	editor.Init();
}
void GLWidget::paintGL() {
	editor.Update();
}