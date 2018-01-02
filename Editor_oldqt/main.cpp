#include "stdafx.h"
#include "Editor.h"
#include <QtWidgets/QApplication>
#include <iostream>


	int main(int argc, char *argv[])
	{

		QApplication a(argc, argv);
		Editor w;
		w.show();
		
		return a.exec();
	}
