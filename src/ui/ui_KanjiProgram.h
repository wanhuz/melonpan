/********************************************************************************
** Form generated from reading UI file 'KanjiProgram.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KANJIPROGRAM_H
#define UI_KANJIPROGRAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KanjiProgramClass
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *KanjiProgramClass)
    {
        if (KanjiProgramClass->objectName().isEmpty())
            KanjiProgramClass->setObjectName(QString::fromUtf8("KanjiProgramClass"));
        KanjiProgramClass->resize(600, 400);
        centralWidget = new QWidget(KanjiProgramClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 40, 521, 251));
        KanjiProgramClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(KanjiProgramClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        KanjiProgramClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(KanjiProgramClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        KanjiProgramClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(KanjiProgramClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        KanjiProgramClass->setStatusBar(statusBar);

        retranslateUi(KanjiProgramClass);

        QMetaObject::connectSlotsByName(KanjiProgramClass);
    } // setupUi

    void retranslateUi(QMainWindow *KanjiProgramClass)
    {
        KanjiProgramClass->setWindowTitle(QCoreApplication::translate("KanjiProgramClass", "KanjiProgram", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KanjiProgramClass: public Ui_KanjiProgramClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KANJIPROGRAM_H
