#include "stdafx.h"
#include "Editor.h"
#include <GL/glut.h>  // for glutInit
#include "qapplication.h"     // for QApplication
	int main(int argc, char *argv[])
	{
		glutInit(&argc, argv);
		QApplication a(argc, argv);
		Editor w;
		w.show();
		return a.exec();
	}

