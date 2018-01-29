/********************************************************************************
** Form generated from reading UI file 'Editor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOR_H
#define UI_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_EditorClass
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionExit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTreeWidget *treeWidget;
    GLWidget *widget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EditorClass)
    {
        if (EditorClass->objectName().isEmpty())
            EditorClass->setObjectName(QStringLiteral("EditorClass"));
        EditorClass->resize(802, 556);
        actionNew = new QAction(EditorClass);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(EditorClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExit = new QAction(EditorClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(EditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setFrameShape(QFrame::StyledPanel);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setChildrenCollapsible(false);
        treeWidget = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem1);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy1);
        treeWidget->setMaximumSize(QSize(16777215, 16777215));
        treeWidget->setFocusPolicy(Qt::NoFocus);
        treeWidget->setFrameShape(QFrame::StyledPanel);
        treeWidget->setDragEnabled(true);
        treeWidget->setDragDropMode(QAbstractItemView::InternalMove);
        splitter->addWidget(treeWidget);
        widget = new GLWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        splitter->addWidget(widget);

        horizontalLayout->addWidget(splitter);

        EditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 802, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        EditorClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(EditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EditorClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(EditorClass);

        QMetaObject::connectSlotsByName(EditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditorClass)
    {
        EditorClass->setWindowTitle(QApplication::translate("EditorClass", "Editor", Q_NULLPTR));
        actionNew->setText(QApplication::translate("EditorClass", "New", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("EditorClass", "Open", Q_NULLPTR));
        actionExit->setText(QApplication::translate("EditorClass", "Exit", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("EditorClass", "Scene", Q_NULLPTR));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("EditorClass", "One", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("EditorClass", "Child", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem3 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("EditorClass", "Two", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem3->child(0);
        ___qtreewidgetitem4->setText(0, QApplication::translate("EditorClass", "Child2", Q_NULLPTR));
        treeWidget->setSortingEnabled(__sortingEnabled);

        menuFile->setTitle(QApplication::translate("EditorClass", "File", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("EditorClass", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EditorClass: public Ui_EditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
