/********************************************************************************
** Form generated from reading UI file 'MainFrame.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFRAME_H
#define UI_MAINFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMainFrameClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CMainFrameClass)
    {
        if (CMainFrameClass->objectName().isEmpty())
            CMainFrameClass->setObjectName(QStringLiteral("CMainFrameClass"));
        CMainFrameClass->resize(600, 400);
        menuBar = new QMenuBar(CMainFrameClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CMainFrameClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CMainFrameClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CMainFrameClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CMainFrameClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CMainFrameClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CMainFrameClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CMainFrameClass->setStatusBar(statusBar);

        retranslateUi(CMainFrameClass);

        QMetaObject::connectSlotsByName(CMainFrameClass);
    } // setupUi

    void retranslateUi(QMainWindow *CMainFrameClass)
    {
        CMainFrameClass->setWindowTitle(QApplication::translate("CMainFrameClass", "CMainFrame", 0));
    } // retranslateUi

};

namespace Ui {
    class CMainFrameClass: public Ui_CMainFrameClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFRAME_H
