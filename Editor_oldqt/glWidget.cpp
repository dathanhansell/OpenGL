#include "stdafx.h"
#include "glWidget.h"

glWidget::glWidget(QWidget *parent)
	: QGLWidget(parent)
{
	connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	timer.start(16);
}

glWidget::~glWidget()
{
}
