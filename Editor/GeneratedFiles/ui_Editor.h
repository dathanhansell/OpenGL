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
#include <QtWidgets/QWidget>
#include "glwidget.h"
#include "hierarchyview.h"

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
    HierarchyView *treeWidget;
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
        treeWidget = new HierarchyView(splitter);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setAcceptDrops(true);
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
        menuFile->setTitle(QApplication::translate("EditorClass", "File", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("EditorClass", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EditorClass: public Ui_EditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
