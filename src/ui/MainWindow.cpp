#include "MainWindow.h"
#include <QtWidgets/qlineedit.h>
#include <qstandarditemmodel.h>
#include <qmainwindow.h>
#include <qtextcodec.h>
#include <Windows.h>
#include "../capturekey/maincontroller.h"



MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    OCRBtn = ui.ocrBtn;
    textBtn = ui.textBtn;
    textbox = ui.textLine;
    table = ui.dictView;
    
    MainControl = new MainController();
    QStringList labels;
    labels.insert(0, QString("Kanji"));
    labels.insert(1, QString("Kana"));
    labels.insert(2, QString("Meaning"));
    dictmodel.setHorizontalHeaderLabels(labels);
    
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    OCRBtn->setCheckable(true);
    textBtn->setCheckable(true);
    table->verticalHeader()->setVisible(false);


    table->setModel(&dictmodel);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(MainControl, SIGNAL(OcrResult(QString)), textbox, SLOT(setText(QString)));
    connect(OCRBtn, SIGNAL(toggled(bool)), this, SLOT(startCaptureOCR(bool)));
    connect(OCRBtn, SIGNAL(toggled(bool)), this, SLOT(alwaysOnTop(bool)));
    connect(textBtn, SIGNAL(toggled(bool)), this, SLOT(startCaptureText(bool)));
    connect(textbox, SIGNAL(textChanged(QString)), this, SLOT(search()));
}


void MainWindow::search() {
    dictmodel.clear();
    QString searchText = textbox->text();
    QVector<QStringList> searchResult = MainControl->searchDict(searchText);
    if (searchResult[0].size() == 0) {
       //No result found
    }
    else if (searchResult[0].at(0).isEmpty()) {
        //No kanji found
        dictmodel.clear();
    }
    else {
        for (int i = 0; i < searchResult[0].size(); i++) {
            dictmodel.setItem(i, 0, new QStandardItem(searchResult[0].at(i).toLocal8Bit().constData()));
            dictmodel.setItem(i, 1, new QStandardItem(searchResult[1].at(i).toLocal8Bit().constData()));
            dictmodel.setItem(i, 2, new QStandardItem(searchResult[2].at(i).toLocal8Bit().constData()));
        }
    }

    QStringList labels;
    labels.insert(0, QString("Kanji"));
    labels.insert(1, QString("Kana"));
    labels.insert(2, QString("Meaning"));
    dictmodel.setHorizontalHeaderLabels(labels);


}

void MainWindow::startCaptureOCR(bool enableOCR) {
    if (!enableOCR) {
        MainControl->stopCaptureKey();
    }
    else {
        MainControl->startCaptureKeyOCR();
    }
    
}

void MainWindow::startCaptureText(bool enableText){
    if (!enableText) {
        MainControl->stopCaptureKey();
    }
    else {
        MainControl->startCaptureKeyTextGeneric();
    }
}

void MainWindow::alwaysOnTop(bool enabled) {
    this->showNormal();
    HWND hwnd = (HWND)this->winId();
    if (enabled) {
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    }
    else {
        SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    }

}