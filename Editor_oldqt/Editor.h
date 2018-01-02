#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Editor.h"

class Editor : public QMainWindow
{
	Q_OBJECT

public:
	Editor(QWidget *parent = Q_NULLPTR);

private:
	Ui::EditorClass ui;
};
