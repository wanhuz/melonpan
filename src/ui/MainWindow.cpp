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


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QEventLoop eventloop;
    OCRBtn = ui.ocrBtn;
    textbox = ui.textLine;
    table = ui.dictView;
    frame = new Frame();
    QStandardItemModel* model = new QStandardItemModel(14, 2);

    //Dict dict;
    //dict.load();
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    
    OCRBtn->setCheckable(true);
    table->verticalHeader()->setVisible(false);
    
    DictLoader* dictloader = new DictLoader();
    table->setModel(dictloader->getModel());
    dictloader->start();
    
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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


