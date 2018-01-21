#pragma once

#include "ui_Editor.h"
#include "qcompilerdetection.h"  // for Q_NULLPTR
#include "qmainwindow.h"         // for QMainWindow
#include "qobjectdefs.h"         // for Q_OBJECT
#include "qstring.h"             // for QString
	class Editor : public QMainWindow
	{
		Q_OBJECT

	public:
		Editor(QWidget *parent = Q_NULLPTR);

	private:
		Ui::EditorClass ui;
	};
