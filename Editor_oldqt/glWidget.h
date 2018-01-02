#pragma once
#include <QTimer>
#include <QGLWidget>
class glWidget : public QGLWidget
{
	Q_OBJECT

public:
	glWidget(QWidget *parent);
	~glWidget();
private:
	QTimer timer;
};
