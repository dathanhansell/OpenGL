#pragma once

#include "QSFMLWidget.h"
#include "EditorLoop.h"
class QWidget;

	class SFMLCanvas : public QSFMLWidget
	{
	public:
		SFMLCanvas(QWidget *parent);

		void onInit() override;
		void onUpdate() override;

	private:
		EditorLoop m_editor;
	};

