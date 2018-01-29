#include "stdafx.h"
#include "SFMLCanvas.h"
#include "SFML/Graphics/RenderWindow.hpp"  // for RenderWindow


	SFMLCanvas::SFMLCanvas(QWidget *parent) : QSFMLWidget(parent)
	{
		
	}

	void SFMLCanvas::onInit() {
		m_editor.Init();
	}

	void SFMLCanvas::onUpdate() {
		m_editor.Update();
	}

