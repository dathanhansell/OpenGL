#include "stdafx.h"
#include "HierarchyView.h"

HierarchyView::HierarchyView(QWidget *parent)
	: QTreeWidget(parent)
{

	ChangeOpenHeaderTitle("New Scene");
	open.Hierarchy.AddChild("root1");
	open.Hierarchy.children[0]->AddChild("child1");
	open.Hierarchy.children[0]->AddChild("child1.1");
	open.Hierarchy.children[0]->children[0]->AddChild("grandchild1");
	open.Hierarchy.children[0]->ChangeParent(open.Hierarchy.children[0]->children[0]);
	CreateFromScene(open);
		

}
void HierarchyView::ChangeOpenHeaderTitle(QString title) {
	setHeaderLabel(title);
}
QTreeWidgetItem* HierarchyView::AddRoot(QString name) {
	QTreeWidgetItem *itm = new QTreeWidgetItem();
	itm->setText(0, name);
	addTopLevelItem(itm);
	return itm;
}
QTreeWidgetItem * HierarchyView::AddChild(QTreeWidgetItem *parent, QString name) {
	QTreeWidgetItem *itm = new QTreeWidgetItem();
	itm->setText(0, name);
	parent->addChild(itm);
	return itm;
}
void HierarchyView::ChildAdd(Node* node, QTreeWidgetItem *parent) {
	QTreeWidgetItem *itm = AddChild(parent, QString::fromStdString(node->name));
	for (int x = 0; x < node->children.size(); x++) {
		ChildAdd(node->children[x],itm);
	};
	
}
void HierarchyView::CreateFromScene(Scene scene) {
	for (int x = 0; x < scene.Hierarchy.children.size(); x++) {
		QTreeWidgetItem *itm = AddRoot(QString::fromStdString(scene.Hierarchy.children[x]->name));
		for (int y = 0; y < scene.Hierarchy.children[x]->children.size(); y++) {
			ChildAdd(scene.Hierarchy.children[x]->children[y], itm);
		}
	};
};