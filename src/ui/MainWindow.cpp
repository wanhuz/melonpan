#include "MainWindow.h"
#include <QtWidgets/qlineedit.h>
#include <qstandarditemmodel.h>
#include <qstring.h>
#include <qmainwindow.h>
#include <QKeyEvent>
#include "../util/util.h"
#include "../ocr/ocr.h"
#include <qtextcodec.h>
#include "../dict/dict.h"
#include "../dict/DictLoader.h"
#include <qdebug.h>
#include <qstandarditemmodel.h>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    OCRBtn = ui.ocrBtn;
    textbox = ui.textLine;
    table = ui.dictView;
    frame = new Frame();
    DictLoader* dictloader = new DictLoader();
    ocr = new Ocr();
    
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    OCRBtn->setCheckable(true);
    table->verticalHeader()->setVisible(false);
    dictloader->setDict(&dict);
    dictloader->start();

    table->setModel(&dictmodel);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(OCRBtn, SIGNAL(clicked()), this, SLOT(hideFrame()));
    connect(textbox, SIGNAL(textChanged(QString)), this, SLOT(search()));
}


void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (OCRBtn->isChecked()) {
        
        if (event->key() == Qt::Key_F2) {
            frame->hide();
            frame->setBoxSize();
            QPixmap screenshot = frame->shootScreenshot();
            Pix* pix = Util::qPixMap2PIX(&screenshot);
            QString text = ocr->recognize(pix);
            textbox->setText(text);
            frame->show();

            this->activateWindow();
        }
    }
}

void MainWindow::hideFrame() { frame->hide(); }

void MainWindow::search() {
    QString searchText = textbox->text();
    QStringList searchResult = dict.search(searchText);
    if (searchResult.isEmpty()) {
        qDebug() << "No result found";
    }
    else {
        
        for (int i = 0; i < searchResult.size(); i++) {
            dictmodel.setItem(i, new QStandardItem(searchResult.at(i).toLocal8Bit().constData()));
        }
    }

    //QString searchString = textbox->text();
    //QList<QStandardItem*> list = dictmodel->findItems(searchString, Qt::MatchContains, 0);
    //
    //for (int i = 0; i < list.size(); i++) {
    //    textbox->setText(list.at(i)->text());

    //}

}