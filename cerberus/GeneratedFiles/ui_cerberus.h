/********************************************************************************
** Form generated from reading UI file 'cerberus.ui'
**
** Created: Mon Feb 13 11:53:47 2012
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CERBERUS_H
#define UI_CERBERUS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cerberusClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *cerberusClass)
    {
        if (cerberusClass->objectName().isEmpty())
            cerberusClass->setObjectName(QString::fromUtf8("cerberusClass"));
        cerberusClass->resize(600, 400);
        menuBar = new QMenuBar(cerberusClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        cerberusClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(cerberusClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        cerberusClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(cerberusClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        cerberusClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(cerberusClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        cerberusClass->setStatusBar(statusBar);

        retranslateUi(cerberusClass);

        QMetaObject::connectSlotsByName(cerberusClass);
    } // setupUi

    void retranslateUi(QMainWindow *cerberusClass)
    {
        cerberusClass->setWindowTitle(QApplication::translate("cerberusClass", "cerberus", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class cerberusClass: public Ui_cerberusClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CERBERUS_H
