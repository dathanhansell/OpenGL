#pragma once

#include <QtOpenGL/qgl.h>
#include <QGLWidget>
#include <Game.h>
class GLWidget : public QGLWidget
{
	Q_OBJECT
		
public:
	explicit GLWidget(QWidget *parent = 0);
	//virtual ~GLWidget();
protected:
	void initializeGL();
	void paintGL();

	void resizeGL(int width, int height);
	Game editor;
};
