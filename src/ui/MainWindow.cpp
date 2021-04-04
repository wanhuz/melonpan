#include "MainWindow.h"
#include <QtWidgets/qlineedit.h>
#include <qstandarditemmodel.h>
#include <qmainwindow.h>
#include <qtextcodec.h>
#include <Windows.h>
#include "../capturekey/maincontroller.h"
#include <qaction.h>
#include <qdebug.h>
#include "../settings/config.h"
#include "../ui/SettingsWindow.h";
#include <qfontdatabase.h>
#include <qdir.h>
#include <qfile.h>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    OCRBtn = ui.ocrBtn;
    textBtn = ui.textBtn;
    textbox = ui.textLine;
    table = ui.dictView;
    QAction* fsSmall = ui.fs_small;
    QAction* fsNormal = ui.fs_normal;
    QAction* fsLarge = ui.fs_large;
    QAction * fsvLarge = ui.fs_verylarge;
    QAction* frameVert = ui.actionVertical;
    QAction* frameHort = ui.actionHorizontal;
    QAction* settingsWindow = ui.Settings;
    MainControl = new MainController();

    QString fontPath = QDir::currentPath();
    fontPath = "C:\\Users\\WanHuz\\Documents\\Shanachan\\res\\";
    fontPath = fontPath + "NotoSansMonoCJKjp-Regular.otf";
    int id = QFontDatabase::addApplicationFont(fontPath);
    
    if (id < 0) {
        qDebug() << "Failed to load Sans Mono JK font at " << fontPath;
    }
    else {
        QString NotoJK = QFontDatabase::applicationFontFamilies(id).at(0);
        sansMonoJK = new QFont(NotoJK, 12);
    }


    //UI customization
    
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
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //Connect menu bar button
    connect(fsSmall, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameSize(15);
        });
    connect(fsNormal, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameSize(30);
        });
    connect(fsLarge, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameSize(45);
        });
    connect(fsvLarge, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameSize(60);
        });
    connect(frameVert, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameOrientation(true);
        });
    connect(frameHort, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameOrientation(false);
        });
    connect(settingsWindow, &QAction::triggered, this, [=]() {
            SettingsWindow* settings = new SettingsWindow();;
            settings->show();
        });


    //Connect buttons to respective function
    connect(MainControl, SIGNAL(OcrResult(QString)), textbox, SLOT(setText(QString)));
    connect(OCRBtn, SIGNAL(toggled(bool)), this, SLOT(startCaptureOCR(bool)));
    connect(OCRBtn, SIGNAL(toggled(bool)), this, SLOT(alwaysOnTop(bool)));
    connect(textBtn, SIGNAL(toggled(bool)), this, SLOT(startCaptureText(bool)));
    connect(textBtn, SIGNAL(toggled(bool)), this, SLOT(alwaysOnTop(bool)));
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
    else if (searchResult[0].size() > 0) {
        QFile file("exampledebug.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "No file found";
            return;
        }
            

        QTextStream out(&file);

        for (int i = 0; i < searchResult[0].size(); i++) {
            out << searchResult[0].at(i) << endl;
            dictmodel.setItem(i, 0, new QStandardItem(searchResult[0].at(i).toLocal8Bit().constData()));
            dictmodel.setItem(i, 1, new QStandardItem(searchResult[1].at(i).toLocal8Bit().constData()));
            dictmodel.setItem(i, 2, new QStandardItem(searchResult[2].at(i).toLocal8Bit().constData()));
        }

        //If font is found, set the font to Sans Mono JK
        if (sansMonoJK != NULL) {
            for (int i = 0; i < dictmodel.rowCount(); i++) {
                dictmodel.item(i, 0)->setFont(*sansMonoJK);
                dictmodel.item(i, 1)->setFont(*sansMonoJK);
            }
        }


    }

    //Refresh UI
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
