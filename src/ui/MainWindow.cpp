#include "MainWindow.h"
#include <QtWidgets/qlineedit.h>
#include <qstandarditemmodel.h>
#include <qstring.h>
#include <qmainwindow.h>
#include <QKeyEvent>
#include "../util/util.h"
#include "../ocr/ocr.h"
#include <qtextcodec.h>



MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    OCRBtn = ui.ocrBtn;
    textbox = ui.textLine;
    table = ui.dictView;
    frame = new Frame();
    QStandardItemModel* model = new QStandardItemModel(14, 2);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    
    OCRBtn->setCheckable(true);
    table->verticalHeader()->setVisible(false);
    table->setModel(model);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    model->appendRow(new QStandardItem(QString("lol")));
    //for (int row = 0; row < model->rowCount(); ++row) {
    //    for (int column = 0; column < model->columnCount(); ++column) {
    //        QStandardItem* item = new QStandardItem(QString("row %0, column %1").arg(row).arg(column));
    //        model->setItem(row, column, item);
    //    }
    //}
    ocr = new Ocr();
    connect(OCRBtn, SIGNAL(clicked()), this, SLOT(hideFrame()));
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

void MainWindow::hideFrame() {

    frame->hide();
    
}


