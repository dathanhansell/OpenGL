#include "stdafx.h"
#include "HierarchyView.h"

HierarchyView::HierarchyView(QWidget *parent)
	: QTreeWidget(parent)
{
	setHeaderLabel("New Scene");
	QTreeWidgetItem *itm = new QTreeWidgetItem();
	itm->setText(0,"dop");
	addTopLevelItem(itm);

		

}
