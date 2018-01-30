#pragma once
#include <Scene.h>
#include <QObject>

class HierarchyView : public QTreeWidget
{
	Q_OBJECT
		void ChildAdd(Node node, QTreeWidgetItem *parent);
public:
	explicit HierarchyView(QWidget *parent);
	void HierarchyView::ChangeOpenHeaderTitle(QString title);
	QTreeWidgetItem* HierarchyView::AddRoot(QString name);
	QTreeWidgetItem * HierarchyView::AddChild(QTreeWidgetItem *parent, QString name);
	void HierarchyView::CreateFromScene(Scene scene);
	Scene open;
};
