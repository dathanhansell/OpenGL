#pragma once

#ifdef Q_WS_X11
#include <QT/qx11info_x11.h>
#include <X11\Xlib.h>
#endif
#include "qobjectdefs.h"                   // for Q_OBJECT
#include "qstring.h"                       // for QString
#include "qtimer.h"                        // for QTimer
#include "qwidget.h"                       // for QWidget
#include "SFML/Graphics/RenderWindow.hpp"  // for RenderWindow


class QSFMLWidget : public QWidget, public sf::RenderWindow
{
	Q_OBJECT

public:
	explicit QSFMLWidget(QWidget *parent);

	virtual QPaintEngine *paintEngine() const;

	virtual void showEvent(QShowEvent *event);
	virtual void paintEvent(QPaintEvent *event);
	virtual void onInit();
	virtual void onUpdate();
	
private:

	QTimer m_timer;
	bool m_initialized;
};
