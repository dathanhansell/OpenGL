#pragma once

#include <QObject>

class HierarchyView : public QTreeWidget
{
	Q_OBJECT

public:
	explicit HierarchyView(QWidget *parent);
};
