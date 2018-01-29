#pragma once

#include "QSFMLWidget.h"
#include <Game.h>
class QWidget;

	class SFMLCanvas : public QSFMLWidget
	{
	public:
		SFMLCanvas(QWidget *parent);

		void onInit() override;
		void onUpdate() override;

	private:
		Game m_editor;
	};

