#include "MainWindow.h"
#include <QtWidgets/qlineedit.h>
#include <qstandarditemmodel.h>
#include <qmainwindow.h>
#include <QKeyEvent>
#include "../util/util.h"
#include "../ocr/ocr.h"
#include <qtextcodec.h>
#include "../dict/dict.h"
#include "../dict/DictLoader.h"
#include <qdebug.h>



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
    QStringList labels;
    labels.insert(0, QString("Kanji"));
    labels.insert(1, QString("Kana"));
    labels.insert(2, QString("Meaning"));
    dictmodel.setHorizontalHeaderLabels(labels);
    
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
    dictmodel.clear();
    QString searchText = textbox->text();
    QVector<QStringList> searchResult = dict.search(searchText);
    if (searchResult[0].size() == 0) {
        qDebug() << "No result found";
    }
    else if (searchResult[0].at(0).isEmpty()) {
        qDebug() << "No kanji found";
        dictmodel.clear();
    }
    else {
        for (int i = 0; i < searchResult[0].size(); i++) {
            dictmodel.setItem(i, 0, new QStandardItem(searchResult[0].at(i).toLocal8Bit().constData()));
            dictmodel.setItem(i, 1, new QStandardItem(searchResult[1].at(i).toLocal8Bit().constData()));
            dictmodel.setItem(i, 2, new QStandardItem(searchResult[2].at(i).toLocal8Bit().constData()));
        }
    }


}