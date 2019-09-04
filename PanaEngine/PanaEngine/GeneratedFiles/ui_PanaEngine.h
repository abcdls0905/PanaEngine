/********************************************************************************
** Form generated from reading UI file 'PanaEngine.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANAENGINE_H
#define UI_PANAENGINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

#include "OpenglWindow.h"

QT_BEGIN_NAMESPACE

class Ui_PanaEngineClass
{
public:
    QWidget *centralWidget;
	OpenglWindow *openGLWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PanaEngineClass)
    {
        if (PanaEngineClass->objectName().isEmpty())
            PanaEngineClass->setObjectName(QStringLiteral("PanaEngineClass"));
        PanaEngineClass->resize(1366, 768);
        centralWidget = new QWidget(PanaEngineClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        openGLWidget = new OpenglWindow(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 1366, 768));
        PanaEngineClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PanaEngineClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1366, 23));
        PanaEngineClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PanaEngineClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PanaEngineClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PanaEngineClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PanaEngineClass->setStatusBar(statusBar);

        retranslateUi(PanaEngineClass);

        QMetaObject::connectSlotsByName(PanaEngineClass);
    } // setupUi

    void retranslateUi(QMainWindow *PanaEngineClass)
    {
        PanaEngineClass->setWindowTitle(QApplication::translate("PanaEngineClass", "PanaEngine", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PanaEngineClass: public Ui_PanaEngineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANAENGINE_H
